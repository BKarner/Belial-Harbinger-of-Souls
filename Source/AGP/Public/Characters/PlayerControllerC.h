// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "PlayerCharacter.h"
#include "PlayerControllerC.generated.h"

/**
*
*/
UCLASS()
class AGP_API APlayerControllerC : public APlayerController {
	GENERATED_UCLASS_BODY()

		bool bIsMouseBeingHeld; // Used to check that the character can still move towards the direction of the mouse

	/** Utility Functions */
	void MoveInMouseDirection();

	/** Mouse 'n KeyboardInput Delegates */
	void MouseOn(); void MouseOff();
	void StandAttack();
	void OnFire();
	void Debug();

protected:
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
};

