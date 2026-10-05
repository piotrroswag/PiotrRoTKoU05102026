#pragma once

#include "CoreMinimal.h"
#include "Action/Logic/WrActionLogicBasic.h"
#include "WrActionLogicRoaming.generated.h"

class UWrActionRoamingData;

// 
UCLASS()
class WORLDREACTIVITY_API UWrActionLogicRoaming : public UWrActionLogicBasic
{
	GENERATED_BODY()

public:
	virtual void Begin() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupData(UWrActionData* Data) override;

private:
	UPROPERTY()
	TObjectPtr<UWrActionRoamingData> ActionRoamingData;
	float TimeCounter = 0.0f;
};
