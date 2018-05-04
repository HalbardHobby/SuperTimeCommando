// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AIEnemyPatrolController.h"
#include "BTSetState.generated.h"

/**
 * 
 */
UCLASS()
class SUPERTIMECOMMANDO_API UBTSetState : public UBTTaskNode
{
	GENERATED_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& Owner, uint8* Node) override;
	
public:
	UPROPERTY(EditAnywhere)
	EPatrolStateEnum NewState;
};