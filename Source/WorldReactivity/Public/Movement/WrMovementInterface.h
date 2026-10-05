#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WrMovementInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UWrMovementInterface : public UInterface
{
	GENERATED_BODY()
};

// Movement interface.
class WORLDREACTIVITY_API IWrMovementInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Wr")
	void ExecuteMoveToLocation(const FVector& TargetLocation);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Wr")
	void ExecuteMoveToRandomLocation();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Wr")
	void ExecuteStopMovement();
};