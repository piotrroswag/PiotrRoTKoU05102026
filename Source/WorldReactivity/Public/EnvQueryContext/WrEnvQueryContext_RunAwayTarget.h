#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "WrEnvQueryContext_RunAwayTarget.generated.h"

// Query context related to finding the best point on the navmesh.
UCLASS()
class WORLDREACTIVITY_API UWrEnvQueryContext_RunAwayTarget : public UEnvQueryContext
{
	GENERATED_BODY()
	
public:
	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;
};
