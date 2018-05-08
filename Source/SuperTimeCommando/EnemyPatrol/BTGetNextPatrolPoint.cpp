// Fill out your copyright notice in the Description page of Project Settings.

#include "BTGetNextPatrolPoint.h"
#include "AIEnemyPatrolController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Int.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UBTGetNextPatrolPoint::ExecuteTask(UBehaviorTreeComponent & Owner, uint8 * Node)
{
	AAIEnemyPatrolController* AIPatrol = Cast<AAIEnemyPatrolController>(Owner.GetAIOwner());

	if (AIPatrol) 
	{
		UBlackboardComponent* BlackboardComp = AIPatrol->GetBlackboardComponent();
	}

	return EBTNodeResult::Succeeded;
}
