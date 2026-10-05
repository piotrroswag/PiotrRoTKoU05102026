#pragma once

#include "CoreMinimal.h"
#include "WrActionData.h"
#include "Action/Logic/WrActionLogicPlayAudio.h"
#include "Misc/DataValidation.h"
#include "Sound/SoundBase.h"
#include "WrActionPlayAudioData.generated.h"

UCLASS(BlueprintType)
class WORLDREACTIVITY_API UWrActionPlayAudioData : public UWrActionData
{
	GENERATED_BODY()

public:
	UWrActionPlayAudioData()
	{
		LogicClass = UWrActionLogicPlayAudio::StaticClass();
	}
	
	virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wr")
	TObjectPtr<class USoundBase> Sound;
};

inline EDataValidationResult UWrActionPlayAudioData::IsDataValid(FDataValidationContext& Context) const
{
	EDataValidationResult Result = Super::IsDataValid(Context);

	if (!IsValid(Sound))
	{
		Context.AddWarning(NSLOCTEXT("UWrActionPlayAudioData", "Invalid", "Sound is invalid!"));
	}

	return Result;
}
