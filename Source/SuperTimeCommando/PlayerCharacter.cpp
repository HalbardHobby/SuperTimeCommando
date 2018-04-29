// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

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

	// Cuadrar parametros adicionales
	CameraRotationSpeed = 5.f;
	CharacterRotationSpeed = 5.f;

	MaxCameraOffsetDistance = 150.f;
	CameraOffsetScale = 0.3f;
	CameraOffsetSpeed = 2.f;
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	LookAtCursor(DeltaTime);
	OffsetCameraToCursor(DeltaTime);
}

void APlayerCharacter::LookAtCursor(float DeltaTime)
{
	// Se obtiene la posición del cursor
	FHitResult CursorToWorldPosition;
	APlayerController* Controller =  GetWorld()->GetFirstPlayerController();
	Controller->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), true, CursorToWorldPosition);
	FVector Direction = GetActorLocation() - CursorToWorldPosition.Location;
	
	FRotator TargetRotation = FRotationMatrix::MakeFromZ(Direction).Rotator();
	TargetRotation.Pitch = 0.f;
	TargetRotation.Roll = 0.f;

	FRotator TargetInterpolation = FMath::RInterpTo(GetActorRotation(), TargetRotation, DeltaTime, CharacterRotationSpeed);
	SetActorRotation(TargetInterpolation);
}

void APlayerCharacter::OffsetCameraToCursor(float DeltaTime)
{
	// Se obtiene la posición del cursor
	FHitResult CursorToWorldPosition;
	APlayerController* Controller = GetWorld()->GetFirstPlayerController();
	Controller->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), true, CursorToWorldPosition);
	FVector Direction = GetActorLocation() - CursorToWorldPosition.Location;
	
	float DistanceOffset = Direction.Size() * CameraOffsetScale;

	float DistanceInterpolation = FMath::FInterpTo(CameraBoom->RelativeLocation.Y, DistanceOffset, DeltaTime, CameraOffsetSpeed);
	DistanceInterpolation = FMath::Clamp<float>(DistanceInterpolation, 0.f, MaxCameraOffsetDistance);

	CameraBoom->SetRelativeLocation(FVector(0.f, DistanceInterpolation, 0.f));
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

	//bind de las acciones
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("TurnRight", this, &APlayerCharacter::TurnRight);
}

void APlayerCharacter::MoveForward(float Value)
{
	//Tomar plano xy del vector frontal de la camara
	FVector Direction = PlayerCameraComponent->GetForwardVector();
	Direction.Z = 0.f;

	Direction.Normalize();
	AddMovementInput(Direction, Value);
}

void APlayerCharacter::MoveRight(float Value)
{
	//Tomar plano xy del vector derecha de la camara
	FVector Direction = PlayerCameraComponent->GetRightVector();
	Direction.Z = 0.f;

	Direction.Normalize();
	AddMovementInput(Direction, Value);
}

void APlayerCharacter::TurnRight(float Value)
{
	FRotator* DeltaRotation = new FRotator( 0.f, Value * CameraRotationSpeed, 0.f );

	CameraBoom->AddWorldRotation( *DeltaRotation );
}