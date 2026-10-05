#include "WorldTimeSystem/WrWorldTimeSubsystem.h"

#include "Engine/World.h"
#include "Log/WrLog.h"
#include "WorldTimeSystem/WrWorldTimeConfig.h"

void UWrWorldTimeSubSystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	TObjectPtr<const UWrWorldTimeConfig> WorldTimeConfig = GetDefault<UWrWorldTimeConfig>();
	
	GameTimespan = FTimespan::FromHours(WorldTimeConfig->HourGameBegin) +
				   FTimespan::FromMinutes(WorldTimeConfig->MinuteGameBegin);
	TimeScale = static_cast<float>(WorldTimeConfig->InGameHoursPerRealMinute) * 60.0f;
}

void UWrWorldTimeSubSystem::Tick(float DeltaTime)
{
	const float GameSecondsPassed = DeltaTime * TimeScale;
	GameTimespan += FTimespan::FromSeconds(GameSecondsPassed);
	
	OnGameTimeChanged.Broadcast(GameTimespan);
}

ETickableTickType UWrWorldTimeSubSystem::GetTickableTickType() const
{
	if (IsTemplate())
	{
		return ETickableTickType::Never;
	}

	return ETickableTickType::Conditional;
}

bool UWrWorldTimeSubSystem::IsTickable() const
{
	if (!Super::IsTickable())
	{
		return false;
	}
	
	return !IsTemplate() && GetWorld();
}

TStatId UWrWorldTimeSubSystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UWrWorldTimeSubSystem, STATGROUP_Tickables);
}