#pragma once

#include "CoreMinimal.h"
#include "Action/Logic/WrActionLogicBasic.h"
#include "Context/WrActorCaughtActorEventContext.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "WrActionLogicRunaway.generated.h"

class UWrActionRunawayData;

// 
UCLASS()
class WORLDREACTIVITY_API UWrActionLogicRunaway : public UWrActionLogicBasic
{
	GENERATED_BODY()

public:
	virtual void Begin() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupData(UWrActionData* Data) override;
	
	TObjectPtr<AActor> GetRunawayTarget() const { return RunAwayTarget; }
	
private:
	void OnEscapePointFound(TSharedPtr<FEnvQueryResult> QueryResult);
	void RunAway();

	UPROPERTY()
	TObjectPtr<UWrActionRunawayData> ActionRunawayData;
	UPROPERTY()
	TObjectPtr<AActor> RunAwayTarget;
	float LastRunAwayTime = 0.0f;
	float RunAwayDurationCounter = 0.0f;
};
