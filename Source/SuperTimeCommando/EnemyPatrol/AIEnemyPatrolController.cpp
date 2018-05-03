// Fill out your copyright notice in the Description page of Project Settings.

#include "AIEnemyPatrolController.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"


AAIEnemyPatrolController::AAIEnemyPatrolController()
{
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIVision"));
	//AISightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfiguration"));
	//AIPerception->ConfigureSense(*AISightConfig);
	
	AIPerception->OnPerceptionUpdated.AddDynamic(this, &AAIEnemyPatrolController::OnPerceptionUpdated);

	PatrolBehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("PatrolBehavior"));
	PatrolBlackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("PatrolBlackboard"));
}

void AAIEnemyPatrolController::BeginPlay()
{

}

void AAIEnemyPatrolController::Tick(float DeltaTime)
{

}

void AAIEnemyPatrolController::Possess(APawn* possessedPawn) 
{
	Super::Possess(possessedPawn);
}

void AAIEnemyPatrolController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{

}