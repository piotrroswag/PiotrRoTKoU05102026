#include "Action/Logic/WrActionLogicRoaming.h"

#include "Action/Data/WrActionRoamingData.h"
#include "GameFramework/Actor.h"
#include "Movement/WrMovementInterface.h"

void UWrActionLogicRoaming::Begin()
{
	if (ActorOwner->GetClass()->ImplementsInterface(UWrMovementInterface::StaticClass()))
	{
		IWrMovementInterface::Execute_ExecuteMoveToRandomLocation(ActorOwner.Get());
	}
}

void UWrActionLogicRoaming::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeCounter += DeltaTime;
	if (TimeCounter >= ActionRoamingData->RoamingInterval)
	{
		TimeCounter -= ActionRoamingData->RoamingInterval;

		if (ActorOwner->GetClass()->ImplementsInterface(UWrMovementInterface::StaticClass()))
		{
			IWrMovementInterface::Execute_ExecuteMoveToRandomLocation(ActorOwner.Get());
		}
	}
}

void UWrActionLogicRoaming::SetupData(UWrActionData* Data)
{
	ActionRoamingData = Cast<UWrActionRoamingData>(Data);
}
