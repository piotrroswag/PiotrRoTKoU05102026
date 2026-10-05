#include "Action/Logic/WrActionLogicRunaway.h"

#include "EngineUtils.h"
#include "Action/Data/WrActionRunawayData.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "GameFramework/Actor.h"
#include "Log/WrLog.h"
#include "Movement/WrMovementInterface.h"

void UWrActionLogicRunaway::Begin()
{
	for (TActorIterator<AActor> It(GetWorld(), ActionRunawayData->RunAwayFromActor); It; ++It)
	{
		if (AActor* FoundActor = *It)
		{
			RunAwayTarget = FoundActor;
			break;
		}
	}

	if (IsValid(RunAwayTarget))
	{
		RunAway();
	}
	else
	{
		bFinished = true;
		UE_LOG(LogWr, Warning, TEXT("UWrActionLogicRunaway. Cannot find actor to run away from!"));
	}
}

void UWrActionLogicRunaway::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsValid(RunAwayTarget))
	{
		bFinished = true;
		UE_LOG(LogWr, Warning, TEXT("UWrActionLogicRunaway. RunAwayTarget is invalid"));
		return;
	}
	
	RunAwayDurationCounter += DeltaTime;

	// Actor run away for some time. Now needs to stop, to allow to chase.
	if (RunAwayDurationCounter >= ActionRunawayData->RunAwayDuration)
	{
		IWrMovementInterface::Execute_ExecuteStopMovement(ActorOwner);
	}
	else
	{
		if (LastRunAwayTime + ActionRunawayData->RunAwayUpdateInterval <= GetWorld()->GetTimeSeconds())
		{
			RunAway();
		}
	}
}

void UWrActionLogicRunaway::RunAway()
{
	if (!IsValid(ActionRunawayData->EscapeQueryAsset))
	{
		bFinished = true;
		return;
	}
	
	LastRunAwayTime = GetWorld()->GetTimeSeconds();
	FEnvQueryRequest QueryRequest(ActionRunawayData->EscapeQueryAsset, ActorOwner);
	QueryRequest.Execute(EEnvQueryRunMode::SingleResult, this, &UWrActionLogicRunaway::OnEscapePointFound);
}

void UWrActionLogicRunaway::OnEscapePointFound(TSharedPtr<FEnvQueryResult> QueryResult)
{
	if (!QueryResult.IsValid() || !QueryResult->IsSuccessful())
	{
		return;
	}
	
	TArray<FVector> OutLocations;
	QueryResult->GetAllAsLocations(OutLocations);
	
	if (OutLocations.Num() > 0)
	{
		const FVector BestEscapeLocation = OutLocations[0];
		IWrMovementInterface::Execute_ExecuteMoveToLocation(ActorOwner, BestEscapeLocation);
	}
}

void UWrActionLogicRunaway::SetupData(UWrActionData* Data)
{
	ActionRunawayData = Cast<UWrActionRunawayData>(Data);
}