// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_AlertEveryone.h"


UBTTask_AlertEveryone::UBTTask_AlertEveryone(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Alert Everyone";
}

EBTNodeResult::Type UBTTask_AlertEveryone::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	return EBTNodeResult::Type();
}
