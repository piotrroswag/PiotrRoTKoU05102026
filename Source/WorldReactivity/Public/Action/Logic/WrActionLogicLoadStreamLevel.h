#pragma once

#include "CoreMinimal.h"
#include "Action/Logic/WrActionLogicBasic.h"
#include "WrActionLogicLoadStreamLevel.generated.h"

class UWrActionLoadStreamLevelData;

// 
UCLASS()
class WORLDREACTIVITY_API UWrActionLogicLoadStreamLevel : public UWrActionLogicBasic
{
	GENERATED_BODY()

public:
	virtual void Begin() override;
	virtual void SetupData(UWrActionData* Data) override;
	
private:
	void LoadGameExtensionLevel(FName LevelName);
	UFUNCTION()
	void OnExtensionLevelLoaded();

	UPROPERTY()
	TObjectPtr<UWrActionLoadStreamLevelData> ActionLoadStreamLevelData;
};
