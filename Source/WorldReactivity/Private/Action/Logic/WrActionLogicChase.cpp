#include "Action/Logic/WrActionLogicChase.h"

#include "EngineUtils.h"
#include "Action/Data/WrActionChaseData.h"
#include "Context/WrEventContext.h"
#include "Engine/World.h"
#include "EventSystem/WrEventSubsystem.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Log/WrLog.h"
#include "Movement/WrMovementInterface.h"

void UWrActionLogicChase::Begin()
{
	for (TActorIterator<AActor> It(GetWorld(), ActionChaseData->ActorToChase); It; ++It)
	{
		if (AActor* FoundActor = *It)
		{
			ChaseTarget = FoundActor;

			break;
		}
	}

	if (IsValid(ChaseTarget))
	{
		Chase();
	}
	else
	{
		bFinished = true;
		UE_LOG(LogWr, Warning, TEXT("UWrActionLogicChase. Cannot find actor to chase!"));
	}
}

void UWrActionLogicChase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsValid(ChaseTarget))
	{
		bFinished = true;
		UE_LOG(LogWr, Warning, TEXT("UWrActionLogicChase. ChaseTarget is invalid"));
		return;
	}
	
	// Caught condition.
	if (FVector::DistSquared(ActorOwner->GetActorLocation(), ChaseTarget->GetActorLocation())
		<= ActionChaseData->CaptureDistance * ActionChaseData->CaptureDistance)
	{
		IWrMovementInterface::Execute_ExecuteStopMovement(ActorOwner);
		
		for (const TObjectPtr<const UWrEventActionData>& Event : ActionChaseData->EventsAfterCaught)
		{
			if (!IsValid(Event.Get()))
			{
				continue;
			}
			
			if (UWrEventSubSystem* EventSubSystem = GetWorld()->GetSubsystem<UWrEventSubSystem>())
			{				
				UWrEventContext* EventContext = NewObject<UWrEventContext>(this);

				FWrContextValue ContextValue;
				ContextValue.VectorValue = ActorOwner->GetActorLocation();
				EventContext->Values.Emplace(EValueType::CaughtPlace, ContextValue);
				EventSubSystem->AddAdditionalEvent(Event, EventContext);
			}
		}

		bFinished = true;
	}
	// Still NOT capture target.
	else
	{
		// If target move to another place invoke MoveTo method again.
		// or after small amount of time 1.5f sec since last MoveTo.
		if (FVector::DistSquared(ChaseTarget->GetActorLocation(), ChasePosition)
			> (ActionChaseData->CaptureDistance * 0.5f) * (ActionChaseData->CaptureDistance * 0.5f))
		{
			Chase();
		}
		else if (LastSearchTime + ActionChaseData->PathUpdateInterval <= GetWorld()->GetTimeSeconds())
		{
			Chase();
		}
	}
}

void UWrActionLogicChase::Chase()
{
	if (!IsValid(ChaseTarget))
	{
		return;
	}
	
	LastSearchTime = GetWorld()->GetTimeSeconds();
	ChasePosition = ChaseTarget->GetActorLocation();
	IWrMovementInterface::Execute_ExecuteMoveToLocation(ActorOwner, ChasePosition);
}

void UWrActionLogicChase::SetupData(UWrActionData* Data)
{
	ActionChaseData = Cast<UWrActionChaseData>(Data);
}