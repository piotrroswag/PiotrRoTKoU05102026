#include "EventSystem/WrWorldTimeEventConfig.h"

#include "Misc/App.h"

FName UWrWorldTimeEventConfig::GetCategoryName() const
{
	return FApp::GetProjectName();
}

#if WITH_EDITOR
void UWrWorldTimeEventConfig::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	
	const FName MemberPropertyName = (PropertyChangedEvent.MemberProperty != nullptr) ? PropertyChangedEvent.MemberProperty->GetFName() : NAME_None;
	
	if (MemberPropertyName == GET_MEMBER_NAME_CHECKED(UWrWorldTimeEventConfig, TimedEvents))
	{
		Algo::Sort(TimedEvents, [](const FTimeEventRow& A, const FTimeEventRow& B)
		{
			return A.GetTotalSeconds() <= B.GetTotalSeconds();
		});
		
		Modify();
		SaveConfig();
	}
}
#endif