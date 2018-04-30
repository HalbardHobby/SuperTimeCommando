// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
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

	/** Vertices del cono procedural */
	TArray<FVector> ConeVertices;

	/** Triangulos del cono de visión */
	TArray<uint32> ConeTriangles;
	
private:
	/** Cono de visión */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = VisionCone, meta = (AllowPrivateAccess = "true"))
	class UProceduralMeshComponent* VisionConeMesh;
	
	/** Query de alcance del cono de visión */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = VisionCone, meta = (AllowPrivateAccess = "true"))
	class UEnvQuery* VisionConeReach;
};
