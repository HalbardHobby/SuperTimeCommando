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

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Retorna el subcomponente c�mara. **/
	FORCEINLINE class UCameraComponent* GetPlayerCameraComponent() const { return PlayerCameraComponent; }
	/** Retorna el cubcomponente de boom de c�mara*/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Funci�n para movimiento lateral */
	void MoveRight(float Val);

	/** Funci�n para la rotaci�n de la c�mara */
	void TurnRight(float Val);

	/** Funci�n para movimiento frontal */
	void MoveForward(float Val);

	/** Funci�n para el offset de la c�mara */
	void OffsetCameraToCursor(float DeltaTime);

	/** Funci�n para la rotaci�n del personaje */
	void LookAtCursor(float DeltaTime);

	/** Velocidad a la que rota la c�mara */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CameraMovement)
	float CameraRotationSpeed;

	/** M�xima distancia que puede alejarse la c�mara del jugador */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CameraMovement)
	float MaxCameraOffsetDistance;

	/** Escala a la que se desplaza la camara con respecto al cursor */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CameraMovement)
	float CameraOffsetScale;

	/** Velocidad a la que se spuede mover la c�mara. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CameraMovement)
	float CameraOffsetSpeed;

	/** Velocidad a la que rota la c�mara */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Movement)
	float CharacterRotationSpeed;


private:
	/** Camara del jugador */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* PlayerCameraComponent;

	/** Boom de la camara sobre el personaje */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;


};
