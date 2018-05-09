// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_SetSearchLocation.generated.h"

/**
 * 
 */
UCLASS()
class SUPERTIMECOMMANDO_API UBTTask_SetSearchLocation : public UBTTask_BlackboardBase
{
	GENERATED_UCLASS_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector LastKnownLoactionKey;

	UPROPERTY(EditAnywhere)
	float SearchRadius;
};
