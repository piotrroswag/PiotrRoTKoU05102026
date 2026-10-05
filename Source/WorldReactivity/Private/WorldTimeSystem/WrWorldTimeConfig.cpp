#include "WorldTimeSystem/WrWorldTimeConfig.h"

#include "Misc/App.h"

FName UWrWorldTimeConfig::GetCategoryName() const
{
	return FApp::GetProjectName();
}
