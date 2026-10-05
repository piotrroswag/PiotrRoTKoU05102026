#pragma once

#include "CoreMinimal.h"
#include "Action/Logic/WrActionLogicBasic.h"
#include "WrActionLogicDisplayName.generated.h"

class UWrActionDisplayNameData;

// 
UCLASS()
class WORLDREACTIVITY_API UWrActionLogicDisplayName : public UWrActionLogicBasic
{
	GENERATED_BODY()

public:
	virtual void Begin() override;
	virtual void SetupData(UWrActionData* Data) override;
	
private:
	UPROPERTY()
	TObjectPtr<UWrActionDisplayNameData> ActionDisplayNameData;
};
