// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_SetState.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Enum.h"
#include "EnemyPatrol/AIEnemyPatrolController.h"


UBTTask_SetState::UBTTask_SetState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Set State";
}

EBTNodeResult::Type UBTTask_SetState::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	Blackboard->SetValueAsEnum(CurrentStateKey.SelectedKeyName, (uint8)NewState);

	return EBTNodeResult::Succeeded;
}
