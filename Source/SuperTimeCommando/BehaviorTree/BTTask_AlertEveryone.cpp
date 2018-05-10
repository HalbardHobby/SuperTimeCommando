// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_AlertEveryone.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TimeCommandoGameMode.h"
#include "Engine.h"

UBTTask_AlertEveryone::UBTTask_AlertEveryone(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Alert Everyone";

	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_AlertEveryone, BlackboardKey));
}

EBTNodeResult::Type UBTTask_AlertEveryone::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	ATimeCommandoGameMode* GameMode = Cast<ATimeCommandoGameMode>(GetWorld()->GetAuthGameMode());
	GameMode->OnEnemyLocated.Broadcast(Blackboard->GetValueAsVector(BlackboardKey.SelectedKeyName));
	return EBTNodeResult::Succeeded;
}
