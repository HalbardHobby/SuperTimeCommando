// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_SetSearchLocation.h"
#include "AI/Navigation/NavigationSystem.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "EnemyPatrol/AIEnemyPatrolController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "EnemyPatrol/EnemyPatrol.h"


UBTTask_SetSearchLocation::UBTTask_SetSearchLocation(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Set Search Location";

	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_SetSearchLocation, BlackboardKey));
	LastKnownLoactionKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_SetSearchLocation, BlackboardKey));
}

EBTNodeResult::Type UBTTask_SetSearchLocation::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	FNavLocation* NewLocation = new FNavLocation();
	
	UNavigationSystem::GetCurrent(GetWorld())->GetRandomReachablePointInRadius(Blackboard->GetValueAsVector(LastKnownLoactionKey.SelectedKeyName), SearchRadius, *NewLocation);

	Blackboard->SetValueAsVector(BlackboardKey.SelectedKeyName, NewLocation->Location);

	return EBTNodeResult::Succeeded;
}
