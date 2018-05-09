// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_SetSearchLocation.h"


UBTTask_SetSearchLocation::UBTTask_SetSearchLocation(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Set Search Location";
}

EBTNodeResult::Type UBTTask_SetSearchLocation::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	return EBTNodeResult::Type();
}
