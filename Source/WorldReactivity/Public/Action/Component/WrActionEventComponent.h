#pragma once

#include "CoreMinimal.h"
#include "Action/Data/WrActionData.h"
#include "Components/ActorComponent.h"
#include "Action/Logic/WrActionLogicBasic.h"
#include "WrActionEventComponent.generated.h"

class UWrActionLogicRunaway;
class UWrEventContext;
class UWrEventActionData;

// Component that subscribe for gameplay event. 
// It serves as the primary location for managing actions, data, and contexts.
UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent))
class WORLDREACTIVITY_API UWrActionEventComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UWrActionEventComponent();

	const UWrActionLogicRunaway* GetActionLogicRunaway() const;
	
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// Filter allowing you to specify which actions will be handled by the component.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wr")
	TArray<TSubclassOf<UWrActionData>> FilterAction;
	
private:
	UFUNCTION()
	void OnEventActionTriggered(const UWrEventActionData* EventAction, const UWrEventContext* Context);

	UPROPERTY()
	TArray<TObjectPtr<UWrActionLogicBasic>> ActiveActions;
};
