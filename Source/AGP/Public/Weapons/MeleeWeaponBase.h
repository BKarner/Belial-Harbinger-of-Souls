// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WeaponBase.h"
#include "MeleeWeaponBase.generated.h"

/**
 * 
 */
UCLASS()
class AGP_API AMeleeWeaponBase : public AWeaponBase{
	GENERATED_UCLASS_BODY()

	// Short sword = 50cm

	/** Does the weapon have advanced attack function? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	bool advancedAttack;

	/** Basic melee attack function */
	UFUNCTION(BlueprintCallable, Category = Attack)
		void Attack(AAGPCharacter* User);

	/** Length of the weapon */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults")
	float weaponReach = 150.0f;

};

