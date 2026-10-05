#pragma once

#include "CoreMinimal.h"
#include "WrActionData.h"
#include "Action/Logic/WrActionLogicDisplayName.h"
#include "Misc/DataValidation.h"
#include "WrActionDisplayNameData.generated.h"

UCLASS(BlueprintType)
class WORLDREACTIVITY_API UWrActionDisplayNameData : public UWrActionData
{
	GENERATED_BODY()

public:
	UWrActionDisplayNameData()
	{
		LogicClass = UWrActionLogicDisplayName::StaticClass();
	}
	
	virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wr")
	FName Name = "";
};

inline EDataValidationResult UWrActionDisplayNameData::IsDataValid(FDataValidationContext& Context) const
{
	EDataValidationResult Result = Super::IsDataValid(Context);

	if (Name.IsNone())
	{
		Context.AddWarning(NSLOCTEXT("UWrActionDisplayNameData", "Invalid", "Name is none!"));
	}

	return Result;
}
