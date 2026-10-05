#include "PlayerController/WrPlayerController.h"

#include "Log/WrLog.h"
#include "Blueprint/UserWidget.h"
#include "UI/WrGameWidget.h"

void AWrPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsValid(GameWidgetClass))
	{
		GameWidget = CreateWidget<UWrGameWidget>(this, GameWidgetClass);
		GameWidget->AddToViewport();
	}
	else
	{
		UE_LOG(LogWr, Log, TEXT("AWrPlayerController::BeginPlay. GameWidget is null!"));
	}
}
