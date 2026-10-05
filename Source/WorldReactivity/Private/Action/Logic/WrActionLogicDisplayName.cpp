#include "Action/Logic/WrActionLogicDisplayName.h"

#include "Action/Data/WrActionDisplayNameData.h"
#include "Engine/World.h"
#include "EventSystem/WrEventSubsystem.h"

void UWrActionLogicDisplayName::Begin()
{
	Super::Begin();

	if (const UWrEventSubSystem* EventSubSystem = GetWorld()->GetSubsystem<UWrEventSubSystem>())
	{
		EventSubSystem->OnDisplayNameChanged.Broadcast(ActionDisplayNameData->Name);
	}

	bFinished = true;
}

void UWrActionLogicDisplayName::SetupData(UWrActionData* Data)
{
	ActionDisplayNameData = Cast<UWrActionDisplayNameData>(Data);
}