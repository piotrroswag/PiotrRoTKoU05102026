#pragma once

#include "CoreMinimal.h"
#include "WrEventCondition.h"
#include "WrEventConditionPlayerInsideRadius.generated.h"

UCLASS(BlueprintType, Blueprintable)
class WORLDREACTIVITY_API UWrEventConditionPlayerInsideRadius : public UWrEventCondition
{
	GENERATED_BODY()
 
public:
	virtual bool IsMet(const UWrEventContext* Context) const override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Wr)
	float Distance = 500;
};
