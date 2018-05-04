// Fill out your copyright notice in the Description page of Project Settings.

#include "AIEnemyPatrolController.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "EnemyPatrol.h"
#include "Engine.h"


AAIEnemyPatrolController::AAIEnemyPatrolController()
{
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIVision"));
	AISightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfiguration"));
	
	AISightConfig->SightRadius = 1100.f;
	AISightConfig->LoseSightRadius = 1150.f;
	AISightConfig->PeripheralVisionAngleDegrees = 30.f;
	AISightConfig->DetectionByAffiliation.bDetectEnemies = true;
	AISightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	AISightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	AIPerception->ConfigureSense(*AISightConfig);
	AIPerception->SetDominantSense(AISightConfig->GetSenseImplementation());
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
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "I see you!");
}