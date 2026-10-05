#pragma once

#include "CoreMinimal.h"
#include "WrActionData.h"
#include "Action/Logic/WrActionLogicLoadStreamLevel.h"
#include "Misc/DataValidation.h"
#include "WrActionLoadStreamLevelData.generated.h"

UCLASS(BlueprintType)
class WORLDREACTIVITY_API UWrActionLoadStreamLevelData : public UWrActionData
{
	GENERATED_BODY()

public:
	UWrActionLoadStreamLevelData()
	{
		LogicClass = UWrActionLogicLoadStreamLevel::StaticClass();
	}
	
	virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wr")
	FName LevelToLoad = "L_ObstaclesExtension";
};

inline EDataValidationResult UWrActionLoadStreamLevelData::IsDataValid(FDataValidationContext& Context) const
{
	EDataValidationResult Result = Super::IsDataValid(Context);

	if (LevelToLoad.IsNone())
	{
		Context.AddWarning(NSLOCTEXT("UWrActionLoadStreamLevelData", "Invalid", "LevelToLoad is none!"));
	}

	return Result;
}
