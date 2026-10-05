#include "EnvQueryContext/WrEnvQueryContext_RunAwayTarget.h"

#include "Action/Component/WrActionEventComponent.h"
#include "Action/Logic/WrActionLogicRunaway.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "NPC/WrNPCCharacter.h"

void UWrEnvQueryContext_RunAwayTarget::ProvideContext(FEnvQueryInstance& QueryInstance,
                                                      FEnvQueryContextData& ContextData) const
{
	AActor* QueryOwner = Cast<AActor>(QueryInstance.Owner.Get());
	if (!QueryOwner)
	{
		return;
	}

	UWrActionEventComponent* ActionEventComponent = QueryOwner->FindComponentByClass<UWrActionEventComponent>();
	if (!IsValid(ActionEventComponent))
	{
		UEnvQueryItemType_Actor::SetContextHelper(ContextData, QueryOwner);
		return;
	}

	const UWrActionLogicRunaway* ActionLogicRunaway = ActionEventComponent->GetActionLogicRunaway();
	if (!IsValid(ActionLogicRunaway))
	{
		UEnvQueryItemType_Actor::SetContextHelper(ContextData, QueryOwner);
		return;
	}

	TObjectPtr<AActor> Target = ActionLogicRunaway->GetRunawayTarget();
	if (!IsValid(Target))
	{
		UEnvQueryItemType_Actor::SetContextHelper(ContextData, QueryOwner);
		return;
	}
	
	UEnvQueryItemType_Actor::SetContextHelper(ContextData, Target);
}
