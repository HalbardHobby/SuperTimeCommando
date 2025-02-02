// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/Character.h"
#include "EnemyPatrol.generated.h"

UCLASS(Blueprintable)
class SUPERTIMECOMMANDO_API AEnemyPatrol : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyPatrol();

	/** Puntos en 3D de la patrulla */
	UPROPERTY(EditInstanceOnly, Category = Patrol)
	TArray<ATargetPoint*> PatrolPath;

	/** Obtiene el siguiente punto de navegaci�n en la patrulla */
	UFUNCTION(BlueprintCallable)
	ATargetPoint* GetPatrolPoint(int index);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Llamado cuando se va a disparar al jugador */
	void FireAtPlayer();

	/** Realiza la primera creaci�n del mesh del cono */
	void CreateVisionCone();

	/** Actualiza el cono cada frame */
	void UpdateVisionCone();

	/** Cantidd de puntos de referencia para el cono */
	UPROPERTY(EditAnywhere, Category = VisionCone)
	uint32 NumberOfReferencePoints;

	/** Angulo de visi�n que cubre el cono */
	UPROPERTY(EditAnywhere, Category = VisionCone)
	float VisionConeAngle;

	/** M�xima distancia que se proyecta el cono */
	UPROPERTY(EditAnywhere, Category = VisionCone)
	float MaxVisionDistance;

	/** Material usado en el cono de visi�n */
	UPROPERTY(EditAnywhere, Category = VisionCone)
	class UMaterial* VisionConeMaterial;
	
	/** Mesh del cono de visi�n */
	UPROPERTY(EditAnywhere, Category = VisionCone)
	class UProceduralMeshComponent* VisionConeMesh;

private:
	/** Sincroniza la rotaci�n del personaje y el controlador */
	void SyncControllerRotation();

	/** Vertices del cono procedural */
	TArray<FVector> VisionConeVertices;

	/** Triangulos del cono de visi�n */
	TArray<int> VisionConeTriangles;

	TArray<FVector> VisionConeNormals;

	TArray<FVector2D> VisionConeUV;

	TArray<FColor> VisionConeColor;

	TArray<FProcMeshTangent> VisionConeTangents;
};
