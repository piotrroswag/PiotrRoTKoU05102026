#pragma once

#include "CoreMinimal.h"
#include "WrActionData.h"
#include "Action/Logic/WrActionLogicMapRestart.h"
#include "WrActionMapRestartData.generated.h"

UCLASS(BlueprintType)
class WORLDREACTIVITY_API UWrActionMapRestartData : public UWrActionData
{
	GENERATED_BODY()

public:
	UWrActionMapRestartData()
	{
		LogicClass = UWrActionLogicMapRestart::StaticClass();
	}
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wr", meta = (Units = "Seconds"))
	float RestartTime = 2.0f;
};