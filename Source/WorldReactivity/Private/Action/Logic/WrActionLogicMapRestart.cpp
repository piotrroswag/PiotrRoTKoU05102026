#include "Action/Logic/WrActionLogicMapRestart.h"

#include "Action/Data/WrActionMapRestartData.h"
#include "Engine/World.h"
#include "EventSystem/WrEventSubsystem.h"
#include "Kismet/GameplayStatics.h"

void UWrActionLogicMapRestart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeCounter += DeltaTime;
	if (TimeCounter >= ActionMapRestartData->RestartTime)
	{
		bFinished = true;

		const FString CurrentLevelName = GetWorld()->GetMapName();
		UGameplayStatics::OpenLevel(GetWorld(), FName(*CurrentLevelName));
	}
	else
	{
		const float Percent = FMath::Clamp(TimeCounter / ActionMapRestartData->RestartTime, 0.0f, 1.0f);
		if (const UWrEventSubSystem* EventSubSystem = GetWorld()->GetSubsystem<UWrEventSubSystem>())
		{
			EventSubSystem->OnFadeoutValueChanged.Broadcast(Percent);
		}
	}
}

void UWrActionLogicMapRestart::SetupData(UWrActionData* Data)
{
	ActionMapRestartData = Cast<UWrActionMapRestartData>(Data);
}
