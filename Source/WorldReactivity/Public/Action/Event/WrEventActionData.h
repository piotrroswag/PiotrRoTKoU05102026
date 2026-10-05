#pragma once

#include "CoreMinimal.h"
#include "Action/Data/WrActionData.h"
#include "Action/Logic/WrActionLogicBasic.h"
#include "Engine/DataAsset.h"
#include "WrEventActionData.generated.h"

class UWrEventCondition;

// Base class describing event data.
UCLASS(BlueprintType)
class WORLDREACTIVITY_API UWrEventActionData : public UDataAsset
{
	GENERATED_BODY()

public:
	// Conditions.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = "Wr")
	TArray<TObjectPtr<UWrEventCondition>> Conditions;
	
	// New action that will be start.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wr")
	TArray<TObjectPtr<UWrActionData>> ActionToStart;
	// Action that needs be stop.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wr")
	TArray<TSubclassOf<UWrActionLogicBasic>> ActionToStop;
};