// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_GetPatrolPoint.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Int.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyPatrol/AIEnemyPatrolController.h"
#include "EnemyPatrol/EnemyPatrol.h"
#include "Engine.h"


UBTTask_GetPatrolPoint::UBTTask_GetPatrolPoint(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "GetPatrolPoint";

	BlackboardKey.AddIntFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_GetPatrolPoint, BlackboardKey));
	TargetLocationKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_GetPatrolPoint, TargetLocationKey));
}

EBTNodeResult::Type UBTTask_GetPatrolPoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AAIEnemyPatrolController* AIOwner = Cast<AAIEnemyPatrolController>(OwnerComp.GetAIOwner());
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	AEnemyPatrol* Patrol = Cast<AEnemyPatrol>(AIOwner->GetOwner());

	int32 Index = Blackboard->GetValueAsInt(BlackboardKey.SelectedKeyName);
	
	ATargetPoint* PatrolPoint = AIOwner->PatrolPath[Index];

	Blackboard->SetValueAsVector(TargetLocationKey.SelectedKeyName, PatrolPoint->GetActorLocation());
	Blackboard->SetValueAsInt(BlackboardKey.SelectedKeyName, (Index + 1)%AIOwner->PatrolPath.Num());

	return EBTNodeResult::Succeeded;
}
