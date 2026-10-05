#pragma once

#include "CoreMinimal.h"
#include "Action/Logic/WrActionLogicBasic.h"
#include "WrActionLogicMapRestart.generated.h"

class UWrActionMapRestartData;

// 
UCLASS()
class WORLDREACTIVITY_API UWrActionLogicMapRestart : public UWrActionLogicBasic
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupData(UWrActionData* Data) override;

private:
	UPROPERTY()
	TObjectPtr<UWrActionMapRestartData> ActionMapRestartData;
	
	float TimeCounter = 0.0f;
};
