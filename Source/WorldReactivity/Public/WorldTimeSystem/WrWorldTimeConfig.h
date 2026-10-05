#pragma once

#include "Engine/DeveloperSettings.h"
#include "Engine/EngineTypes.h"
#include "WrWorldTimeConfig.generated.h"

// Configuration allowing for gameplay time management and setting the initial timestamp.
UCLASS(Config = Game, defaultconfig, BlueprintType, meta = (DisplayName = "WorldTime"))
class WORLDREACTIVITY_API UWrWorldTimeConfig : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	virtual FName GetCategoryName() const override;

	UPROPERTY(config, EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = "0", ClampMax = "23"))
	int HourGameBegin = 10;
	UPROPERTY(config, EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = "0", ClampMax = "59"))
	int MinuteGameBegin = 0;

	// Time scale. 1 in-game hour = real-world minute.
	// For example InGameHoursPerRealMinute=2, per 1 minute real time will pass 2 hours game time.
	UPROPERTY(config, EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = "1", ClampMax = "360"))
	int InGameHoursPerRealMinute = 1;
};
