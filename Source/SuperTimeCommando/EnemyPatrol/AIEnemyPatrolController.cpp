// Fill out your copyright notice in the Description page of Project Settings.

#include "AIEnemyPatrolController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "EnemyPatrol.h"
#include "Engine.h"
#include "Player/PlayerCharacter.h"


AAIEnemyPatrolController::AAIEnemyPatrolController()
{
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIVision"));
	AISightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfiguration"));
	
	AISightConfig->SightRadius = 1100.f;
	AISightConfig->LoseSightRadius = 1150.f;
	AISightConfig->PeripheralVisionAngleDegrees = 30.f;
	AISightConfig->SetMaxAge(15.f);
	AISightConfig->DetectionByAffiliation.bDetectEnemies = true;
	AISightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	AISightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	AIPerception->ConfigureSense(*AISightConfig);
	AIPerception->SetDominantSense(AISightConfig->GetSenseImplementation());
	AIPerception->OnPerceptionUpdated.AddDynamic(this, &AAIEnemyPatrolController::OnPerceptionUpdated);

	PatrolBehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("PatrolBehavior"));
	PatrolBlackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("PatrolBlackboard"));

	PatrolPath = TArray<ATargetPoint*>();
}

void AAIEnemyPatrolController::BeginPlay()
{
	Super::BeginPlay();

	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	PatrolBlackboard->SetValueAsObject("Enemy", PlayerPawn);
}

void AAIEnemyPatrolController::Tick(float DeltaTime)
{

}

void AAIEnemyPatrolController::Possess(APawn* possessedPawn) 
{
	Super::Possess(possessedPawn);
	AEnemyPatrol* Patrol = Cast<AEnemyPatrol>(possessedPawn);

	if (Patrol && PatrolBehavior)
	{
		PatrolPath = Patrol->PatrolPath;
		
		PatrolBlackboard->InitializeBlackboard(*PatrolBehavior->BlackboardAsset);

		PatrolBlackboard->SetValueAsVector("TargetPatrolLocation", Patrol->GetActorLocation());
		PatrolBlackboard->SetValueAsEnum("CurrentState", (uint8)EPatrolStateEnum::PS_Patrolling);
		PatrolBlackboard->SetValueAsInt("PatrolNodeIndex", 0);

		PatrolBehaviorComp->StartTree(*PatrolBehavior);
	}
}

void AAIEnemyPatrolController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	for (int i = 0; i < UpdatedActors.Num(); i++) {
		APlayerCharacter* player = Cast<APlayerCharacter>(UpdatedActors[i]);
		if (player) {

			FActorPerceptionBlueprintInfo* Info = new FActorPerceptionBlueprintInfo();

			AIPerception->GetActorsPerception(player, *Info);

			bool visible = Info->LastSensedStimuli[0].WasSuccessfullySensed();
			FVector KnownLocation = Info->LastSensedStimuli[0].StimulusLocation;

			PatrolBlackboard->SetValueAsBool("IsEnemyVisible", visible);
			PatrolBlackboard->SetValueAsVector("LastKnownLocation", KnownLocation);
		}
	}
}