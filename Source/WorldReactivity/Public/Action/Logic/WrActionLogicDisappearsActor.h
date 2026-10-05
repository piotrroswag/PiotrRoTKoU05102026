#pragma once

#include "CoreMinimal.h"
#include "Action/Logic/WrActionLogicBasic.h"
#include "WrActionLogicDisappearsActor.generated.h"

class UWrActionDisappearsActorData;

// 
UCLASS()
class WORLDREACTIVITY_API UWrActionLogicDisappearsActor : public UWrActionLogicBasic
{
	GENERATED_BODY()

public:
	virtual void Begin() override;
	virtual void SetupData(UWrActionData* Data) override;

private:
	UPROPERTY()
	TObjectPtr<UWrActionDisappearsActorData> ActionDisappearsActorData;
};
