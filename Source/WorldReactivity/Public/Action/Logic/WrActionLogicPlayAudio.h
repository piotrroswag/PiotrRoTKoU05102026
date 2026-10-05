#pragma once

#include "CoreMinimal.h"
#include "Action/Logic/WrActionLogicBasic.h"
#include "WrActionLogicPlayAudio.generated.h"

class UWrActionPlayAudioData;

// 
UCLASS()
class WORLDREACTIVITY_API UWrActionLogicPlayAudio : public UWrActionLogicBasic
{
	GENERATED_BODY()

public:
	virtual void Begin() override;
	virtual void SetupData(UWrActionData* Data) override;

private:
	UPROPERTY()
	TObjectPtr<UWrActionPlayAudioData> ActionPlayAudioData;
};
