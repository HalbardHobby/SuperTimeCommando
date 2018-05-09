// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_AttackEnemy.h"


UBTTask_AttackEnemy::UBTTask_AttackEnemy(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Attack Enemy";
}

EBTNodeResult::Type UBTTask_AttackEnemy::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	return EBTNodeResult::Type();
}
