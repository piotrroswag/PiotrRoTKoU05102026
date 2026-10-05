#include "Action/Logic/WrActionLogicPlayAudio.h"

#include "Action/Data/WrActionPlayAudioData.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Log/WrLog.h"

void UWrActionLogicPlayAudio::Begin()
{
	if (ActionPlayAudioData->Sound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), ActionPlayAudioData->Sound);
	}
	else
	{
		UE_LOG(LogWr, Warning, TEXT("UWrActionLogicPlayAudio. Sound is invalid!"));
	}
	
	bFinished = true;
}

void UWrActionLogicPlayAudio::SetupData(UWrActionData* Data)
{
	ActionPlayAudioData = Cast<UWrActionPlayAudioData>(Data);
}