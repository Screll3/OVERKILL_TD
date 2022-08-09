// Copyright Epic Games, Inc. All Rights Reserved.

#include "OVERKILL_TDPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "../Character/OVERKILL_TDCharacter.h"
#include "Engine/World.h"

AOVERKILL_TDPlayerController::AOVERKILL_TDPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void AOVERKILL_TDPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}