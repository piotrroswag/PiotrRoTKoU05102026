#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "WrGameWidget.generated.h"

class UWrEventContext;

UCLASS()
class WORLDREACTIVITY_API UWrGameWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
private:
	UFUNCTION()
	void OnGameTimeChanged(const FTimespan& GameTimespan);
	UFUNCTION()
	void OnFadeoutValueChanged(float Percent);
	UFUNCTION()
	void OnDisplayNameChanged(FName Name);
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> ScreenFadeBorder;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TimeText;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> EventNameText;

	const FText TimeFormat = NSLOCTEXT("UI", "GameTimeFormat", "{Hour}:{Minute}");
	FNumberFormattingOptions TwoDigitsOptions;
};