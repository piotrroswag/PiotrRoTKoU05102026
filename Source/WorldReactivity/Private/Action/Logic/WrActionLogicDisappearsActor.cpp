#include "Action/Logic/WrActionLogicDisappearsActor.h"

#include "GameFramework/Actor.h"
#include "Action/Data/WrActionDisappearsActorData.h"

void UWrActionLogicDisappearsActor::Begin()
{
	Super::Begin();

	ActorOwner->Destroy();

	bFinished = true;
}

void UWrActionLogicDisappearsActor::SetupData(UWrActionData* Data)
{
	ActionDisappearsActorData = Cast<UWrActionDisappearsActorData>(Data);
}
