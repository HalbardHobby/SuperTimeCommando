// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VisionCone, meta = (AllowPrivateAccess = "true"))
	int32 NumberOfReferencePoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VisionCone, meta = (AllowPrivateAccess = "true"))
	float VisionConeAngle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VisionCone, meta = (AllowPrivateAccess = "true"))
		float MaxVisionDistance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = VisionCone, meta = (AllowPrivateAccess = "true"))
	class UMaterial* VisionConeMaterial;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = VisionCone, meta = (AllowPrivateAccess = "true"))
	class UProceduralMeshComponent* VisionConeMesh;

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
