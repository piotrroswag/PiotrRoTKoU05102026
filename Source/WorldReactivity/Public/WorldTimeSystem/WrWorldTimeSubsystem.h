#pragma once

#include "Core.h"
#include "Subsystems/WorldSubsystem.h"
#include "WrWorldTimeSubSystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameTimeChangedDelegate, const FTimespan&, GameTimespan);

//
UCLASS(BlueprintType, Blueprintable)
class WORLDREACTIVITY_API UWrWorldTimeSubSystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Wr")
	FOnGameTimeChangedDelegate OnGameTimeChanged;
	
protected:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	virtual void Tick(float DeltaTime) override;

	virtual ETickableTickType GetTickableTickType() const override;
	virtual TStatId GetStatId() const override;
	virtual bool IsTickable() const override;
	
private:
	float ElapsedRealSeconds = 0.0f;
	int TotalStartSeconds = 0;
	int InGameHoursPerRealMinute = 1;

	FTimespan GameTimespan;
	float TimeScale = 1.0f;
	
	// Current index, to prevent copy of UWrWorldTimeEventConfig::TimedEvents
	int CurrentIndex = 0;
};
