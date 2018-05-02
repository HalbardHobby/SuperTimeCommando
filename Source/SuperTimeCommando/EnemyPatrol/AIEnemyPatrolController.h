// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIEnemyPatrolController.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EPatrolStateEnum : uint8
{
	PS_Idle			UMETA(DisplayName = "Idle"),
	PS_Patrolling	UMETA(DisplayName = "Patrolling"),
	PS_Searching	UMETA(DisplayName = "Searching"),
	PS_Attacking	UMETA(DisplayName = "Attacking")
};
UCLASS()
class SUPERTIMECOMMANDO_API AAIEnemyPatrolController : public AAIController
{
	GENERATED_BODY()
	
	
public:
	// Sets default values for this character's properties
	AAIEnemyPatrolController();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Inicialización del controlador
	virtual void BeginPlay() override;
	
	// Llamada cada vez que la percepción es actualizada.
	virtual void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

	UPROPERTY(EditAnywhere, Category = Perception)
	class UAIPerceptionComponent* AIPerception;

	UPROPERTY(EditAnywhere, Category = Perception)
	class UAISenseConfig_Sight* AISightConfig;

};
