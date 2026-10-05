#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WrEventCondition.generated.h"

class UWrEventContext;

// Basic event condition class.
UCLASS(Abstract, BlueprintType, Blueprintable, DefaultToInstanced, EditInlineNew)
class WORLDREACTIVITY_API UWrEventCondition : public UObject
{
	GENERATED_BODY()
 
public:
	bool EvaluateCondition(const UWrEventContext* Context) const 
	{ 
		return IsMet(Context) ^ bNegative; 
	}

protected:
	virtual bool IsMet(const UWrEventContext* Context) const { return false; }

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Wr, meta = (AllowPrivateAccess = "true"))
	bool bNegative = false;
};
