#include "Action/Logic/WrActionLogicLoadStreamLevel.h"

#include "Action/Data/WrActionLoadStreamLevelData.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Log/WrLog.h"

void UWrActionLogicLoadStreamLevel::Begin()
{
	Super::Begin();

	if (ActionLoadStreamLevelData->LevelToLoad.IsNone())
	{
		bFinished = true;
		UE_LOG(LogWr, Warning, TEXT("UWrActionLogicLoadStreamLevel. LevelToLoad is none!"));
		return;
	}
	
	LoadGameExtensionLevel(ActionLoadStreamLevelData->LevelToLoad);
}

void UWrActionLogicLoadStreamLevel::LoadGameExtensionLevel(FName LevelName)
{
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	
	LatentInfo.ExecutionFunction = FName("OnExtensionLevelLoaded"); 
	LatentInfo.Linkage = 1;
	LatentInfo.UUID = 98765;
	
	UGameplayStatics::LoadStreamLevel(GetWorld(), LevelName,
		true, false, LatentInfo);
}

void UWrActionLogicLoadStreamLevel::OnExtensionLevelLoaded()
{
	bFinished = true;
}

void UWrActionLogicLoadStreamLevel::SetupData(UWrActionData* Data)
{
	ActionLoadStreamLevelData = Cast<UWrActionLoadStreamLevelData>(Data);
}