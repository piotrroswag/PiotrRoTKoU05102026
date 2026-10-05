#pragma once

#include "CoreMinimal.h"
#include "WrEventContext.h"
#include "WrActorCaughtActorEventContext.generated.h"

// Context related with 'ActorCaughtActor' event. It keeps distance to player.
UCLASS(Blueprintable, BlueprintType)
class UWrActorCaughtActorEventContext : public UWrEventContext
{
	GENERATED_BODY()
	
public:
	UWrActorCaughtActorEventContext(){}
	
	float CurrentDistanceToPlayer = 0.0f;
	UPROPERTY()
	TObjectPtr<AActor> Chaser;
	UPROPERTY()
	TObjectPtr<AActor> CaughtActor;
};
