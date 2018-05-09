// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "EnemyPatrol/AIEnemyPatrolController.h"
#include "BTTask_SetState.generated.h"

/**
 * 
 */
UCLASS()
class SUPERTIMECOMMANDO_API UBTTask_SetState : public UBTTaskNode
{
	GENERATED_UCLASS_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	UPROPERTY(EditAnywhere)
	EPatrolStateEnum NewState;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector CurrentStateKey;
};
