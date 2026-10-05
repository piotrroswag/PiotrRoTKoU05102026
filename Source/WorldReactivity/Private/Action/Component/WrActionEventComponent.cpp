#include "Action/Component/WrActionEventComponent.h"

#include "DrawDebugHelpers.h"
#include "Action/Condition/WrEventCondition.h"
#include "Action/Event/WrEventActionData.h"
#include "Action/Logic/WrActionLogicRunaway.h"
#include "Context/WrEventContext.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "EventSystem/WrEventSubsystem.h"
#include "Kismet/KismetSystemLibrary.h"

bool bCurrentActionShowDebug = false;
FAutoConsoleVariableRef CVarActionEventComponentShowDebug(
	TEXT("Wr.Debug.EventComponent.ShowDebug"),
	bCurrentActionShowDebug,
	TEXT("Show current active action"),
	ECVF_Cheat);

UWrActionEventComponent::UWrActionEventComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UWrActionEventComponent::BeginPlay()
{
	Super::BeginPlay();

	if (UWrEventSubSystem* EventSubSystem = GetWorld()->GetSubsystem<UWrEventSubSystem>())
	{
		EventSubSystem->OnEventActionTriggered.AddDynamic(this, &UWrActionEventComponent::OnEventActionTriggered);
	}
}

void UWrActionEventComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// First removed action that is finished.
	for (int i = ActiveActions.Num() - 1; i >= 0; i--)
	{
		if (ActiveActions[i]->IsFinished())
		{
			ActiveActions[i]->End();
			ActiveActions.RemoveAt(i);
		}
	}
	
	// Tick all current actions.
	for (TObjectPtr<UWrActionLogicBasic> ActionLogic: ActiveActions)
	{
		ActionLogic->Tick(DeltaTime);
	}

#if WITH_UNREAL_DEVELOPER_TOOLS
	if (bCurrentActionShowDebug && !ActiveActions.IsEmpty())
	{
		FString TextInfo;
		TextInfo.Append("Action: ");
		TextInfo.Append(FString::FromInt(ActiveActions.Num()));

		for (TObjectPtr<UWrActionLogicBasic> ActionLogic: ActiveActions)
		{
			TextInfo.Append("\n");
			TextInfo.Append(ActionLogic->GetClass()->GetName());
		}
		
		if (GEngine)
		{
			DrawDebugString(GetWorld(), GetOwner()->GetActorLocation(),
				TextInfo, nullptr, FColor::Green, 0.0f, false, 2.0f);
		}
	}
#endif
}

void UWrActionEventComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (UWrEventSubSystem* EventSubSystem = GetWorld()->GetSubsystem<UWrEventSubSystem>())
	{
		EventSubSystem->OnEventActionTriggered.RemoveAll(this);
	}
}

void UWrActionEventComponent::OnEventActionTriggered(const UWrEventActionData* EventAction,
	const UWrEventContext* Context)
{
	if (!IsValid(EventAction) || !IsValid(Context))
	{
		return;
	}

	// Check event condition. For now all condition must be met.
	for (const UWrEventCondition* Condition : EventAction->Conditions)
	{
		if (!Condition->EvaluateCondition(Context))
		{
			return;
		}
	}
	
	// Stop current action.
	for (TSubclassOf<UWrActionLogicBasic> ActionToStop : EventAction->ActionToStop)
	{
		for (int i = ActiveActions.Num() - 1; i >= 0; i--)
		{
			TObjectPtr<UWrActionLogicBasic> CurrentAction = ActiveActions[i];
			if (ActionToStop.Get() == CurrentAction.Get()->GetClass())
			{
				CurrentAction->End();
				ActiveActions.RemoveAt(i);
			}
		}
	}
	
	// Start new actions.
	for (TObjectPtr<UWrActionData> SingleAction : EventAction->ActionToStart)
	{
		if (!IsValid(SingleAction))
		{
			continue;
		}
		
		if (!FilterAction.Contains(SingleAction->GetClass()))
		{
			continue;
		}

		UWrActionLogicBasic* Logic = nullptr;
		if (UWrActionData* ActionData = Cast<UWrActionData>(SingleAction))
		{
			Logic = NewObject<UWrActionLogicBasic>(this, ActionData->LogicClass);
			Logic->SetupData(ActionData);
			Logic->SetupContext(Context);
			Logic->ActorOwner = GetOwner();
		}

		Logic->Begin();
		ActiveActions.Add(Logic);
	}
}

const UWrActionLogicRunaway* UWrActionEventComponent::GetActionLogicRunaway() const
{
	for (TObjectPtr<UWrActionLogicBasic> ActionLogicBasic : ActiveActions)
	{
		if (const UWrActionLogicRunaway* ActionLogicRunaway = Cast<UWrActionLogicRunaway>(ActionLogicBasic))
		{
			return ActionLogicRunaway;
		}
	}

	return nullptr;
}
