#include "Action/Condition/WrEventConditionPlayerInsideRadius.h"
#include "Context/WrEventContext.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Log/WrLog.h"

bool UWrEventConditionPlayerInsideRadius::IsMet(const UWrEventContext* Context) const
{
	ensure(Context != nullptr);

	if (!Context->Values.Contains(EValueType::CaughtPlace))
	{
		UE_LOG(LogWr, Warning, TEXT("UWrEventConditionPlayerInsideRadius::IsMet. Context does,t contains CaughtPlace value!"));
		return false;
	}

	const FWrContextValue& ContextValue = Context->Values[EValueType::CaughtPlace];
	if (!ContextValue.VectorValue.IsSet())
	{
		UE_LOG(LogWr, Warning, TEXT("UWrEventConditionPlayerInsideRadius::IsMet. CaughtPlace has wrong value type!"));
		return false;
	}
	
	const ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(Context->GetWorld(), 0);
	if (IsValid(PlayerCharacter))
	{
		const float CurrentDistanceToPlayer = FVector::Distance(ContextValue.VectorValue.GetValue(), PlayerCharacter->GetActorLocation());
		return CurrentDistanceToPlayer <= Distance;
	}
	
	return false;
}
