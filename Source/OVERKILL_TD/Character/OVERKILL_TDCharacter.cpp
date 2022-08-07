// Copyright Epic Games, Inc. All Rights Reserved.

#include "OVERKILL_TDCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"

AOVERKILL_TDCharacter::AOVERKILL_TDCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AOVERKILL_TDCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
	MovementTick(DeltaSeconds);
}

void AOVERKILL_TDCharacter::SetupPlayerInputComponent(UInputComponent* InputComponent1)
{
	Super::SetupPlayerInputComponent(InputComponent1);

	InputComponent1->BindAxis(TEXT("MoveForward"), this, &AOVERKILL_TDCharacter::InputAxisX);
	InputComponent1->BindAxis(TEXT("MoveRight"), this, &AOVERKILL_TDCharacter::InputAxisY);
}

void AOVERKILL_TDCharacter::InputAxisX(float Value)
{
	AxisX = Value;
}

void AOVERKILL_TDCharacter::InputAxisY(float Value)
{
	AxisY = Value;
}

void AOVERKILL_TDCharacter::MovementTick(float DeltaTime)
{
	AddMovementInput(FVector(1.f, 0.f, 0.f), AxisX);
	AddMovementInput(FVector(0.f, 1.f, 0.f), AxisY);

	APlayerController* myController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (myController)
	{
		FHitResult HitRes;
		myController->GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery3, false, HitRes);
		SetActorRotation(
			FQuat(
				FRotator(
					0.f,
					UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), HitRes.Location).Yaw,
					0.f
				)
			)
		);
	}
}

void AOVERKILL_TDCharacter::CharacterUpdate()
{
	float ResSpeed = 800.f;
	switch (MovementState)
	{
	case EMovementState::Walk_State:
		ResSpeed = MovementInfo.WalkSpeed;
		break;
	case EMovementState::Run_State:
		ResSpeed = MovementInfo.RunSpeed;
		break;
	case EMovementState::Aim_State:
		ResSpeed = MovementInfo.AimSpeed;
		break;
	default:
		break;
	}
	
	GetCharacterMovement()->MaxWalkSpeed = ResSpeed;
}

void AOVERKILL_TDCharacter::ChangeMovementState(EMovementState NewMovementState)
{
	MovementState = NewMovementState;
	CharacterUpdate();
}
