#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WrPlayerController.generated.h"

class UWrGameWidget;

UCLASS()
class WORLDREACTIVITY_API AWrPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wr")
	TSubclassOf<UWrGameWidget> GameWidgetClass;

private:
	UPROPERTY()
	TObjectPtr<UWrGameWidget> GameWidget;
};