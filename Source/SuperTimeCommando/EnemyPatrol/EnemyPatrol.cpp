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
#include "DrawDebugHelpers.h"


// Sets default values
AEnemyPatrol::AEnemyPatrol()
{
	// Cuadrar el tamaño de la capsula
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	// No rotar usando la dirección de la cámara
	bUseControllerRotationPitch = true;
	bUseControllerRotationRoll = true;
	bUseControllerRotationYaw = false;

	// Configurar movimiento de personaje
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Crear cono procedural
	VisionConeMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("VisionConeMesh"));
	VisionConeMesh->SetupAttachment(RootComponent);
	VisionConeMesh->RelativeLocation = FVector(0.f, 0.f, -70.f);

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PatrolPath = TArray<ATargetPoint*>();
}

// Called when the game starts or when spawned
void AEnemyPatrol::BeginPlay()
{
	Super::BeginPlay();
	CreateVisionCone();
}

// Called every frame
void AEnemyPatrol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateVisionCone();
	SyncControllerRotation();
}

void AEnemyPatrol::CreateVisionCone() 
{
	for (uint16 i = 0; i < NumberOfReferencePoints; i++)
	{
		// El cono es un abanico partiendo del actor
		VisionConeTriangles.Add(0);
		VisionConeTriangles.Add(i + 2);
		VisionConeTriangles.Add(i + 1);
	}

	//Inicializar las demás propiedades del mesh
	VisionConeVertices.Init(FVector(0.f, 0.f, 0.f), NumberOfReferencePoints + 1);
	VisionConeNormals.Init(FVector(0.f, 0.f, 1.f), NumberOfReferencePoints + 1);
	VisionConeUV.Init(FVector2D(1.f, 1.f), NumberOfReferencePoints + 1);
	VisionConeUV[0] = FVector2D(0.f, 0.f);
	VisionConeColor.Init(FColor(), NumberOfReferencePoints + 1);
	VisionConeTangents.Init(FProcMeshTangent(0, 1, 0), NumberOfReferencePoints + 1);

	// Se crean valores constantes para la función
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

void AEnemyPatrol::UpdateVisionCone()
{
	FHitResult OutHit;
	FCollisionQueryParams params;

	FVector Start = GetActorLocation();
	FVector End;

	float DeltaVision = VisionConeAngle / (NumberOfReferencePoints - 1);
	float StartingAngle = -VisionConeAngle / 2;
	FRotator CurrentRotation = FRotator(0.f, StartingAngle, 0.f);
	
	for (uint16 i = 1; i <= NumberOfReferencePoints; i++)
	{
		End = CurrentRotation.RotateVector((GetActorForwardVector() * MaxVisionDistance)) + Start;
		CurrentRotation.Yaw += DeltaVision;

		if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECollisionChannel::ECC_Visibility))
			VisionConeVertices[i] = OutHit.Location - Start;
		else
			VisionConeVertices[i] = End - Start;
	}

	const TArray<int> Triangles = VisionConeTriangles;
	const TArray<FVector> Vertices = VisionConeVertices;
	const TArray<FVector> Normals = VisionConeNormals;
	const TArray<FVector2D> UV0 = VisionConeUV;
	const TArray<FColor> Color = VisionConeColor;
	const TArray<FProcMeshTangent> Tangents = VisionConeTangents;

	VisionConeMesh->UpdateMeshSection(0, Vertices, Normals, UV0, Color, Tangents);
	VisionConeMesh->SetMaterial(0, VisionConeMaterial);
	VisionConeMesh->SetWorldRotation(FRotator(0.f, 0.f, 0.f));
}

ATargetPoint* AEnemyPatrol::GetPatrolPoint(int index)
{
	if (PatrolPath.Num() > 0) {
		ATargetPoint* NextPoint = PatrolPath[index];
		return NextPoint;
	}
	return nullptr;
}

void AEnemyPatrol::SyncControllerRotation()
{
	AController* Controller = APawn::GetController();
	Controller->SetControlRotation(GetActorRotation());
}

void AEnemyPatrol::FireAtPlayer()
{

}