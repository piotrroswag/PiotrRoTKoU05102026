#pragma once

#include "CoreMinimal.h"
#include "WrActionData.h"
#include "Action/Logic/WrActionLogicRoaming.h"
#include "WrActionRoamingData.generated.h"

UCLASS(BlueprintType)
class WORLDREACTIVITY_API UWrActionRoamingData : public UWrActionData
{
	GENERATED_BODY()

public:
	UWrActionRoamingData()
	{
		LogicClass = UWrActionLogicRoaming::StaticClass();
	}
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wr", meta = (Units = "Seconds"))
	float RoamingInterval = 2.0f;
};