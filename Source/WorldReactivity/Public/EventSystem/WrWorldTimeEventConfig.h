#pragma once

#include "Engine/EngineTypes.h"
#include "Engine/DeveloperSettings.h"
#include "WrWorldTimeEventConfig.generated.h"

class UWrEventActionData;

USTRUCT(BlueprintType)
struct FTimeEventRow
{
	GENERATED_BODY()

	int GetTotalSeconds() const { return (Hour * 3600) + (Minute * 60); }

	// Collection of events to be triggered at a specified time.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Action Event")
	TArray<TObjectPtr<const UWrEventActionData>> EventActions;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Time Event", meta = (ClampMin = "0", ClampMax = "23"))
	int Hour = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Time Event", meta = (ClampMin = "0", ClampMax = "59"))
	int Minute = 0;
};

// Configuration allowing events to be placed alongside the time.
UCLASS(Config = Game, defaultconfig, BlueprintType, meta = (DisplayName = "Events"))
class WORLDREACTIVITY_API UWrWorldTimeEventConfig : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	virtual FName GetCategoryName() const override;

	// Sorted collection of all time event.
	UPROPERTY(config, EditAnywhere)
	TArray<FTimeEventRow> TimedEvents;

#if WITH_EDITOR
	// Function that allows events to be sorted from earliest to latest based on time.
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};