// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyPatrol.h"
#include "ProceduralMeshComponent.h"
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
AEnemyPatrol::AEnemyPatrol()
{
	// Cuadrar el tamaño de la capsula
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	// No rotar usando la dirección de la cámara
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	// Configurar movimiento de personaje
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Crear cono procedural
	VisionConeMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("VisionConeMesh"));
	VisionConeMesh->SetupAttachment(RootComponent);
	VisionConeMesh->RelativeLocation = FVector(0.f, 0.f, 70.f);
	VisionConeMesh->RelativeRotation = FRotator(0.f, 0.f, 90.f);
	
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyPatrol::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyPatrol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyPatrol::CreateVisionCone() 
{

}

void AEnemyPatrol::UpdateVisionCone()
{

}

void AEnemyPatrol::FireAtPlayer()
{

}