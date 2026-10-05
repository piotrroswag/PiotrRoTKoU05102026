#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Movement/WrMovementInterface.h"
#include "WrNPCCharacter.generated.h"

UCLASS()
class WORLDREACTIVITY_API AWrNPCCharacter : public ACharacter, public IWrMovementInterface
{
	GENERATED_BODY()

public:
	AWrNPCCharacter();

	virtual void ExecuteMoveToLocation_Implementation(const FVector& TargetLocation) override;
	virtual void ExecuteMoveToRandomLocation_Implementation() override;
	virtual void ExecuteStopMovement_Implementation() override;
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Wr")
	void MoveToLocation(const FVector& TargetLocation);

private:
	void MoveToRandomLocation();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wr", meta = (AllowPrivateAccess = "true", Units = "Cm"))
	float PatrolRange = 1000.0f;
	bool bDuringFreePatrol = false;
};