#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Action/Data/WrActionData.h"
#include "Context/WrEventContext.h"
#include "WrActionLogicBasic.generated.h"

// Base class implementing data-related action logic.
UCLASS()
class WORLDREACTIVITY_API UWrActionLogicBasic : public UObject
{
	GENERATED_BODY()
 
public:
	virtual void SetupData(UWrActionData* Data){}
	virtual void SetupContext(const UWrEventContext* Context){}
	
	virtual void Begin(){}
	virtual void Tick(float DeltaTime){}
	virtual void End(){ ActorOwner = nullptr; }

	bool IsFinished() const { return bFinished; }
	
	UPROPERTY()
	TObjectPtr<AActor> ActorOwner;

protected:
	// Flag saying that this action is ready to be delete.
	bool bFinished = false;
};
