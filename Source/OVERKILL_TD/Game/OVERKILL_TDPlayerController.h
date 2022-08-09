// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "OVERKILL_TDPlayerController.generated.h"


UCLASS()
class AOVERKILL_TDPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AOVERKILL_TDPlayerController();

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;

private:
};


