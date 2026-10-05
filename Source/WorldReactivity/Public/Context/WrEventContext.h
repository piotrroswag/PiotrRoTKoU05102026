#pragma once

#include "CoreMinimal.h"
#include "WrEventContext.generated.h"

UENUM()
enum class EValueType : uint8
{
	CaughtPlace
};

USTRUCT()
struct FWrContextValue
{
	GENERATED_BODY()

	TOptional<float> FloatValue;
	TOptional<int> IntValue;
	TOptional<bool> BoolValue;
	TOptional<FVector> VectorValue;
};

// Context related with action logic.
UCLASS(Blueprintable, BlueprintType)
class WORLDREACTIVITY_API UWrEventContext : public UObject
{
	GENERATED_BODY()

public:
	TMap<EValueType, FWrContextValue> Values;
};
