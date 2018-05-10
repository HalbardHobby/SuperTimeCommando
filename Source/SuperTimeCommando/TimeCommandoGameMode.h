// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TimeCommandoGameMode.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnemyLocatedDelegate, const FVector&, SensedLocation);

UCLASS()
class SUPERTIMECOMMANDO_API ATimeCommandoGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FEnemyLocatedDelegate OnEnemyLocated;
	
};
