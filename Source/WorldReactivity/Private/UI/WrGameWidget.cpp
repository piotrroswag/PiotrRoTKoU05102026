#include "UI/WrGameWidget.h"

#include "Components/TextBlock.h"
#include "EventSystem/WrEventSubsystem.h"
#include "WorldTimeSystem/WrWorldTimeSubsystem.h"

void UWrGameWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (TimeText)
	{
		TimeText->SetText(FText::FromString(TEXT("")));
	}
	if (EventNameText)
	{
		EventNameText->SetText(FText::FromString(TEXT("")));
	}
	
	if (const UWorld* World = GetWorld())
	{
		if (UWrWorldTimeSubSystem* TimeSubsystem = World->GetSubsystem<UWrWorldTimeSubSystem>())
		{
			TimeSubsystem->OnGameTimeChanged.AddDynamic(this, &UWrGameWidget::OnGameTimeChanged);
		}
		if (UWrEventSubSystem* EventSubSystem = World->GetSubsystem<UWrEventSubSystem>())
		{
			EventSubSystem->OnFadeoutValueChanged.AddDynamic(this, &UWrGameWidget::OnFadeoutValueChanged);
			EventSubSystem->OnDisplayNameChanged.AddDynamic(this, &UWrGameWidget::OnDisplayNameChanged);
		}
	}

	TwoDigitsOptions.MinimumIntegralDigits = 2;
	TwoDigitsOptions.MaximumIntegralDigits = 2;
}

void UWrGameWidget::NativeDestruct()
{
	if (const UWorld* World = GetWorld())
	{
		if (UWrWorldTimeSubSystem* TimeSubsystem = World->GetSubsystem<UWrWorldTimeSubSystem>())
		{
			TimeSubsystem->OnGameTimeChanged.RemoveAll(this);
		}
		if (UWrEventSubSystem* EventSubSystem = World->GetSubsystem<UWrEventSubSystem>())
		{
			EventSubSystem->OnFadeoutValueChanged.RemoveAll(this);
			EventSubSystem->OnDisplayNameChanged.RemoveAll(this);
		}
	}

	Super::NativeDestruct();
}

void UWrGameWidget::OnGameTimeChanged(const FTimespan& GameTimespan)
{
	if (TimeText)
	{
		FFormatNamedArguments Args;
		Args.Add(TEXT("Hour"), FText::AsNumber(GameTimespan.GetHours(), &TwoDigitsOptions));
		Args.Add(TEXT("Minute"), FText::AsNumber(GameTimespan.GetMinutes(), &TwoDigitsOptions));
		
		TimeText->SetText(FText::Format(TimeFormat, Args));
	}
}

void UWrGameWidget::OnFadeoutValueChanged(float Percent)
{
	const float ClampedAlpha = FMath::Clamp(Percent, 0.0f, 1.0f);
	const FLinearColor FadeColor = FLinearColor(0.0f, 0.0f, 0.0f, ClampedAlpha);
	ScreenFadeBorder->SetBrushColor(FadeColor);
}

void UWrGameWidget::OnDisplayNameChanged(FName Name)
{
	if (EventNameText)
	{
		EventNameText->SetText(FText::FromName(Name));
	}
}
