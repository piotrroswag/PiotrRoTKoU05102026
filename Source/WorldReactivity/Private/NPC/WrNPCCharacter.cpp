#include "NPC/WrNPCCharacter.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"

AWrNPCCharacter::AWrNPCCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
	AIControllerClass = AAIController::StaticClass();
}

void AWrNPCCharacter::BeginPlay()
{
	Super::BeginPlay();

	//bDuringFreePatrol = true;
	//MoveToRandomLocation();
}

void AWrNPCCharacter::ExecuteMoveToLocation_Implementation(const FVector& TargetLocation)
{
	bDuringFreePatrol = false;
	MoveToLocation(TargetLocation);
}

void AWrNPCCharacter::ExecuteMoveToRandomLocation_Implementation()
{
	MoveToRandomLocation();
}

void AWrNPCCharacter::ExecuteStopMovement_Implementation()
{
	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
		AIController->StopMovement();
	}
}

void AWrNPCCharacter::MoveToLocation(const FVector& TargetLocation)
{
	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
		FAIMoveRequest MoveRequest;
		MoveRequest.SetGoalLocation(TargetLocation);
		MoveRequest.SetAcceptanceRadius(50.0f); 
		MoveRequest.SetUsePathfinding(true);
		
		AIController->MoveTo(MoveRequest);
	}
}

void AWrNPCCharacter::MoveToRandomLocation()
{
	UWorld* World = GetWorld();
	if (UNavigationSystemV1* NavigationSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(World))
	{
		FNavLocation RandomLocation;
		if (NavigationSystem->GetRandomReachablePointInRadius(GetActorLocation(), PatrolRange, RandomLocation))
		{
			MoveToLocation(RandomLocation.Location);
		}
	}
}
