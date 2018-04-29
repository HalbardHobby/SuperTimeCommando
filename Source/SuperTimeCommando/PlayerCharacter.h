// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS(Blueprintable)
class SUPERTIMECOMMANDO_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Función para movimiento lateral */
	void MoveRight(float Val);

	/** Función para la rotación de la cámara */
	void TurnRight(float Val);

	/** Función para movimiento frontal */
	void MoveForward(float Val);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Retorna el subcomponente cámara. **/
	FORCEINLINE class UCameraComponent* GetPlayerCameraComponent() const { return PlayerCameraComponent; }
	/** Retorna el cubcomponente de boom de cámara*/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

private:
	/** Camara del jugador */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* PlayerCameraComponent;

	/** Boom de la camara sobre el personaje */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;


};
