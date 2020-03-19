// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WeaponBase.h"
#include "ProjectileBase.h"
#include "RangedWeaponBase.generated.h"

/**
 * 
 */
UCLASS()
class AGP_API ARangedWeaponBase : public AWeaponBase{
	GENERATED_UCLASS_BODY()

	/** Projectile class to spawn when OnFire is called */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AProjectileBase> ProjectileClass;

	/** Fire power range of the weapon */
	float effectiveRange;

	/** Does the weapon have advanced fire function? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Fire)
	bool advancedFire;

	/** Basic ranged attack function */
	UFUNCTION(BlueprintCallable, Category = Fire)
		void Attack(AAGPCharacter * User);
};
