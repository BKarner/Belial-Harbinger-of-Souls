// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AGPCharacter.h"
#include "AICharacter.generated.h"

/**
 * 
 */
UCLASS()
class AGP_API AAICharacter : public AAGPCharacter{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, Category = AI)
	void AttackAttempt();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Player)
		float XPvalue; // The current XP that they AI is worth

	void LevelUp();

	virtual void BeginPlay() override;
	virtual void Die(AAGPCharacter * Killer) override;
};
