// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "Engine/World.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Cuadrar el tamaño de la capsula
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	// No rotar usando la dirección de la cámara
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	// Configurar movimiento de personaje
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Crear boom de la cámara
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true;
	CameraBoom->TargetArmLength = 800.0f;
	CameraBoom->RelativeRotation = FRotator(-60.0f, 0.0f, 0.0f);
	CameraBoom->bDoCollisionTest = false;

	// Crear la cámara
	PlayerCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	PlayerCameraComponent->bUsePawnControlRotation = false;

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Llamado al iniciar el juego
void APlayerCharacter::BeginPlay() 
{
	Super::BeginPlay();

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerCharacter::MoveRight(float Value)
{

}

void APlayerCharacter::TurnRight(float Value)
{

}

void APlayerCharacter::MoveForward(float Value)
{

}