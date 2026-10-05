#pragma once

#include "CoreMinimal.h"
#include "WrActionData.h"
#include "Action/Logic/WrActionLogicDisappearsActor.h"
#include "WrActionDisappearsActorData.generated.h"

UCLASS(BlueprintType)
class WORLDREACTIVITY_API UWrActionDisappearsActorData : public UWrActionData
{
	GENERATED_BODY()

public:
	UWrActionDisappearsActorData()
	{
		LogicClass = UWrActionLogicDisappearsActor::StaticClass();
	}
};