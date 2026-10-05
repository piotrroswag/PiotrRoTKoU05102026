#pragma once

#include "CoreMinimal.h"
#include "WrActionData.h"
#include "Action/Event/WrEventActionData.h"
#include "Action/Logic/WrActionLogicChase.h"
#include "Misc/DataValidation.h"
#include "GameFramework/Actor.h"
#include "WrActionChaseData.generated.h"

UCLASS(BlueprintType)
class WORLDREACTIVITY_API UWrActionChaseData : public UWrActionData
{
	GENERATED_BODY()

public:
	UWrActionChaseData()
	{
		LogicClass = UWrActionLogicChase::StaticClass();
	}
	
	virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wr")
	TSubclassOf<AActor> ActorToChase;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wr")
	float CaptureDistance = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wr", meta = (Units = "Seconds"))
	float PathUpdateInterval = 1.5f;

	// Events that will be triggered after caught. Event can be empty nothing will happen.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wr")
	TArray<TObjectPtr<const UWrEventActionData>> EventsAfterCaught;
};

inline EDataValidationResult UWrActionChaseData::IsDataValid(FDataValidationContext& Context) const
{
	EDataValidationResult Result = Super::IsDataValid(Context);

	if (!IsValid(ActorToChase))
	{
		Context.AddError(NSLOCTEXT("UWrActionChaseData", "Invalid", "Chase Target is invalid!"));
		Result = EDataValidationResult::Invalid;
	}

	return Result;
}
