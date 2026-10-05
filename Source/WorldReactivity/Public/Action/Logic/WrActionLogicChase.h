#pragma once

#include "CoreMinimal.h"
#include "Action/Logic/WrActionLogicBasic.h"
#include "WrActionLogicChase.generated.h"

class UWrActionChaseData;

// 
UCLASS()
class WORLDREACTIVITY_API UWrActionLogicChase : public UWrActionLogicBasic
{
	GENERATED_BODY()

public:
	virtual void Begin() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupData(UWrActionData* Data) override;

private:
	void Chase();

	UPROPERTY()
	TObjectPtr<UWrActionChaseData> ActionChaseData;
	UPROPERTY()
	TObjectPtr<AActor> ChaseTarget;

	float LastSearchTime = 0.0f;
	FVector ChasePosition = FVector::Zero();
};
