// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTAlertEveryone.generated.h"

/**
 * 
 */
UCLASS()
class SUPERTIMECOMMANDO_API UBTAlertEveryone : public UBTTaskNode
{
	GENERATED_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& Owner, uint8* Node) override;
	
};
