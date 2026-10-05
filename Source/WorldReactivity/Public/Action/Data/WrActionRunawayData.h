#pragma once

#include "CoreMinimal.h"
#include "WrActionData.h"
#include "Action/Logic/WrActionLogicRunaway.h"
#include "Misc/DataValidation.h"
#include "GameFramework/Actor.h"
#include "EnvironmentQuery/EnvQuery.h"
#include "WrActionRunawayData.generated.h"

UCLASS(BlueprintType)
class WORLDREACTIVITY_API UWrActionRunawayData : public UWrActionData
{
	GENERATED_BODY()

public:
	UWrActionRunawayData()
	{
		LogicClass = UWrActionLogicRunaway::StaticClass();
	}
	
	virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wr")
	TSubclassOf<AActor> RunAwayFromActor;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wr", meta = (Units = "Seconds"))
	float RunAwayUpdateInterval = 2.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wr", meta = (Units = "Seconds"))
	float RunAwayDuration = 5.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Wr")
	TObjectPtr<UEnvQuery> EscapeQueryAsset;
};

inline EDataValidationResult UWrActionRunawayData::IsDataValid(FDataValidationContext& Context) const
{
	EDataValidationResult Result = Super::IsDataValid(Context);

	if (!IsValid(RunAwayFromActor))
	{
		Context.AddError(NSLOCTEXT("UWrActionRunawayData", "Invalid", "RunAwayFromActor is invalid!"));
		Result = EDataValidationResult::Invalid;
	}

	if (!IsValid(EscapeQueryAsset))
	{
		Context.AddWarning(NSLOCTEXT("UWrActionRunawayData", "Invalid", "EscapeQueryAsset is invalid!"));
	}
	
	return Result;
}
