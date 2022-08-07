// Copyright Epic Games, Inc. All Rights Reserved.


#include "OVERKILL_TDGameMode.h"
#include "OVERKILL_TDPlayerController.h"
#include "../Character/OVERKILL_TDCharacter.h"
#include "UObject/ConstructorHelpers.h"

AOVERKILL_TDGameMode::AOVERKILL_TDGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AOVERKILL_TDPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Player/BP_Player"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/Blueprints/Game/BP_PlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}

//Blueprint'/Game/Blueprints/Player/BP_Player.BP_Player'
//Blueprint'/Game/Blueprints/Game/BP_PlayerController.BP_PlayerController'