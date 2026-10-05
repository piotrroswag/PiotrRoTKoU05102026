#pragma once

#include "Core.h"
#include "Subsystems/WorldSubsystem.h"
#include "WrEventSubSystem.generated.h"

class UWrEventContext;
class UWrEventActionData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEventActionTriggeredDelegate, const UWrEventActionData*,
	Event, const UWrEventContext*, Context);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFadeoutValueChangedDelegate, float, Percent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDisplayNameChangedDelegate, FName, Name);

USTRUCT()
struct FAdditionalEventAction
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<const UWrEventActionData> EventActionData;
	UPROPERTY()
	TObjectPtr<const UWrEventContext> EventContext;
};

// Subsystem responsible for broadcast events and time events (related to WorldTimeEventConfig).
UCLASS(BlueprintType, Blueprintable)
class WORLDREACTIVITY_API UWrEventSubSystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	// 
	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Wr")
	FOnEventActionTriggeredDelegate OnEventActionTriggered;
	
	// Fadeout event
	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Wr")
	FOnFadeoutValueChangedDelegate OnFadeoutValueChanged;
	// Display name event
	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Wr")
	FOnDisplayNameChangedDelegate OnDisplayNameChanged;
	
	void AddAdditionalEvent(const TObjectPtr<const UWrEventActionData>& InEventActionData,
		const TObjectPtr<const UWrEventContext>& InEventContext);
	
protected:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

private:
	UFUNCTION()
	void OnGameTimeChanged(const FTimespan& GameTimespan);

	// Additional event related with gameplay. It occurs during gameplay logic.
	TArray<FAdditionalEventAction> AdditionalEventActionCollection;
	
	// Current index, to prevent copy of UWrWorldTimeEventConfig::TimedEvents
	// Because UWrWorldTimeEventConfig::TimedEvents collection is sorted
	// We can remember current index to start in right position.
	int CurrentIndex = 0;
	
	double LastTotalCurrentSeconds = 0.0;
};
