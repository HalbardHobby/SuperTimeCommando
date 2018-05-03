// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIEnemyPatrolController.generated.h"

/**
 * Enumerador para Estado de la IA
 */
UENUM(BlueprintType)
enum class EPatrolStateEnum : uint8
{
	PS_Idle			UMETA(DisplayName = "Idle"),
	PS_Patrolling	UMETA(DisplayName = "Patrolling"),
	PS_Searching	UMETA(DisplayName = "Searching"),
	PS_Combat		UMETA(DisplayName = "Combat"),
	PS_Guarding		UMETA(DisplayName = "Guarding")
};

/**
 * Enumerador para arquetipo de IA
 */
enum class EPatrolTypeEnum : uint8
{
	PT_Assault		UMETA(DisplayName = "Assault"),
	PT_Range		UMETA(DisplayName = "Range")
};


UCLASS(Blueprintable)
class SUPERTIMECOMMANDO_API AAIEnemyPatrolController : public AAIController
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	AAIEnemyPatrolController();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Possess(APawn* PossessedPawn) override;

	UPROPERTY(EditAnywhere, Category = Behavior)
	class UBehaviorTree* PatrolBehavior;

	FORCEINLINE class UBehaviorTreeComponent* GetPatrolBehaviorComp() const { return PatrolBehaviorComp; }

	FORCEINLINE class UBlackboardComponent* GetPatrolBlackboardComp() const { return PatrolBlackboard; }

protected:
	// Inicialización del controlador
	virtual void BeginPlay() override;
	
	// Llamada cada vez que la percepción es actualizada.
	virtual void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

	UPROPERTY(EditAnywhere, Category = Perception)
	class UAIPerceptionComponent* AIPerception;

	UPROPERTY(EditAnywhere, Category = Perception)
	class UAISenseConfig_Sight* AISightConfig;

	UPROPERTY(EditAnywhere, Category = Behavior)
	class UBehaviorTreeComponent* PatrolBehaviorComp;

	UPROPERTY(EditAnywhere, Category = Behavior)
	class UBlackboardComponent* PatrolBlackboard;
};
