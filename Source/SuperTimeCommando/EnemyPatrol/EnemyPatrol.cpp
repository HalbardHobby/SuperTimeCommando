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
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryTypes.h"


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
	CreateVisionCone();
	VisionConeRequest = FEnvQueryRequest(VisionConeQuery, this);
}

// Called every frame
void AEnemyPatrol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	VisionConeRequest.Execute(EEnvQueryRunMode::AllMatching, this, &AEnemyPatrol::UpdateVisionCone);
}

void AEnemyPatrol::CreateVisionCone() 
{
	for (uint16 i = 0; i < NumberOfReferencePoints; i++)
	{
		// El cono es un abanico partiendo del actor
		VisionConeTriangles.Add(0);
		VisionConeTriangles.Add(i + 1);
		VisionConeTriangles.Add(i + 2);
	}

	//Inicializar las demás propiedades del mesh
	VisionConeNormals.Init(FVector(0.f, 0.f, 1.f), NumberOfReferencePoints + 1);
	VisionConeUV.Init(FVector2D(1.f, 1.f), NumberOfReferencePoints + 1);
	VisionConeUV[0] = FVector2D(0.f, 0.f);
	VisionConeColor.Init(FColor(), NumberOfReferencePoints + 1);
	VisionConeTangents.Init(FProcMeshTangent(0, 1, 0), NumberOfReferencePoints + 1);
}

void AEnemyPatrol::UpdateVisionCone(TSharedPtr<FEnvQueryResult> Result)
{
	Result->GetAllAsLocations(VisionConeVertices);
	FVector ActorLocation = GetActorLocation();

	// Se cambia el marco de referencia por uno local
	for (uint16 i = 0; i < VisionConeVertices.Num(); i++)
		VisionConeVertices[i] = VisionConeVertices[i] - ActorLocation;

	// Se añade el punto de origen
	VisionConeVertices.Insert(FVector(0.f, 0.f, 0.f), 0);

	const TArray<FVector> Vertices = VisionConeVertices;
	const TArray<int> Triangles = VisionConeTriangles;
	const TArray<FVector> Normals = VisionConeNormals;
	const TArray<FVector2D> UV0 = VisionConeUV;
	const TArray<FColor> Color = VisionConeColor;
	const TArray<FProcMeshTangent> Tangents = VisionConeTangents;

	VisionConeMesh->CreateMeshSection(0, Vertices, Triangles, Normals, UV0, Color, Tangents, false);
	VisionConeMesh->SetMaterial(0, VisionConeMaterial);
	VisionConeMesh->SetWorldRotation(FRotator(0.f, 0.f, 0.f));
}

void AEnemyPatrol::FireAtPlayer()
{

}