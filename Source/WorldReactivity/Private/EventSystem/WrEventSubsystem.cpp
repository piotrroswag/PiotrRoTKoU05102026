#include "EventSystem/WrEventSubsystem.h"

#include "Action/Event/WrEventActionData.h"
#include "Context/WrEventContext.h"
#include "Engine/World.h"
#include "EventSystem/WrWorldTimeEventConfig.h"
#include "WorldTimeSystem/WrWorldTimeSubsystem.h"

void UWrEventSubSystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	if (UWrWorldTimeSubSystem* WorldTimeSubSystem = InWorld.GetSubsystem<UWrWorldTimeSubSystem>())
	{
		WorldTimeSubSystem->OnGameTimeChanged.AddDynamic(this, &UWrEventSubSystem::OnGameTimeChanged);
	}
}

void UWrEventSubSystem::OnGameTimeChanged(const FTimespan& GameTimespan)
{
	// Trigger additional event related with gameplay logic.
	if (!AdditionalEventActionCollection.IsEmpty())
	{
		TArray<FAdditionalEventAction> CopyCollection = AdditionalEventActionCollection;
		AdditionalEventActionCollection.Empty();
		
		for (const FAdditionalEventAction& AdditionalEventAction : CopyCollection)
		{
			OnEventActionTriggered.Broadcast(AdditionalEventAction.EventActionData, AdditionalEventAction.EventContext);
		}
	}
	
	// Trigger events related with time.
	TObjectPtr<const UWrWorldTimeEventConfig> EventConfig = GetDefault<UWrWorldTimeEventConfig>();
	int i = CurrentIndex;
	for (; i < EventConfig->TimedEvents.Num(); ++i)
	{
		const int EventTargetSecond = (EventConfig->TimedEvents[i].Hour * 3600) + (EventConfig->TimedEvents[i].Minute * 60);
		if (LastTotalCurrentSeconds < EventTargetSecond && EventTargetSecond <= GameTimespan.GetTotalSeconds())
		{
			for (TObjectPtr<const UWrEventActionData> EventActionData : EventConfig->TimedEvents[i].EventActions)
			{
				if (!IsValid(EventActionData))
				{
					continue;
				}
				
				const UWrEventContext* EventContext = NewObject<UWrEventContext>(this);
				OnEventActionTriggered.Broadcast(EventActionData, EventContext);
			}
			CurrentIndex = i + 1;
			LastTotalCurrentSeconds = GameTimespan.GetTotalSeconds();
		}
	}
}

void UWrEventSubSystem::AddAdditionalEvent(const TObjectPtr<const UWrEventActionData>& InEventActionData,
	const TObjectPtr<const UWrEventContext>& InEventContext)
{
	ensure(InEventActionData);
	ensure(InEventContext);

	FAdditionalEventAction AdditionalEventAction;
	AdditionalEventAction.EventContext = InEventContext;
	AdditionalEventAction.EventActionData = InEventActionData;

	AdditionalEventActionCollection.Add(AdditionalEventAction);
}
