#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WrActionData.generated.h"

// Base class describing gameplay action data.
UCLASS(BlueprintType, Abstract)
class WORLDREACTIVITY_API UWrActionData : public UDataAsset
{
	GENERATED_BODY()

public:
	// Related logic class.
	TSubclassOf<class UWrActionLogicBasic> LogicClass = UObject::StaticClass();
};