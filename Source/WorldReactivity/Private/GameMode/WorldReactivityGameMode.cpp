// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameMode/WorldReactivityGameMode.h"
#include "Character/WorldReactivityCharacter.h"
#include "PlayerController/WrPlayerController.h"
#include "UObject/ConstructorHelpers.h"

AWorldReactivityGameMode::AWorldReactivityGameMode()
{
	PlayerControllerClass = AWrPlayerController::StaticClass();
	
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
