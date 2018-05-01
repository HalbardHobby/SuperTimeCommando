// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/Character.h"
#include "EnemyPatrol.generated.h"

UCLASS()
class SUPERTIMECOMMANDO_API AEnemyPatrol : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyPatrol();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Llamado cuando se va a disparar al jugador */
	void FireAtPlayer();

	/** Realiza la primera creación del mesh del cono */
	void CreateVisionCone();

	/** Actualiza el cono cada frame */
	void UpdateVisionCone();

	/** Cantidd de puntos de referencia para el cono */
	UPROPERTY(EditAnywhere, Category = VisionCone)
	uint32 NumberOfReferencePoints;

	UPROPERTY(EditAnywhere, Category = VisionCone)
	float VisionConeAngle;

	UPROPERTY(EditAnywhere, Category = VisionCone)
	float MaxVisionDistance;

	UPROPERTY(EditAnywhere, Category = VisionCone)
	class UMaterial* VisionConeMaterial;
	
	UPROPERTY(EditAnywhere, Category = VisionCone)
	class UProceduralMeshComponent* VisionConeMesh;

	UPROPERTY(EditAnywhere, Category = Patrol)
	TArray<ATargetPoint*> PatrolPoints;

private:
	/** Vertices del cono procedural */
	TArray<FVector> VisionConeVertices;

	/** Triangulos del cono de visión */
	TArray<int> VisionConeTriangles;

	TArray<FVector> VisionConeNormals;

	TArray<FVector2D> VisionConeUV;

	TArray<FColor> VisionConeColor;

	TArray<FProcMeshTangent> VisionConeTangents;
};
