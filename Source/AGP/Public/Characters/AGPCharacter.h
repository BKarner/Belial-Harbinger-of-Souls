// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "ProjectileBase.h"
#include "WeaponBase.h"
#include "RangedWeaponBase.h"
#include "MeleeWeaponBase.h"
#include "AGPCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AGP_API AAGPCharacter : public ACharacter{
	GENERATED_UCLASS_BODY()

	/** Sphere used for colliding the weapon swing with enemies / objects */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	class USphereComponent * WeaponReachSphere;

	/** Sphere used for colliding the weapon swing with enemies / objects */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
		class UChildActorComponent * WeaponActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		float RangedFireOffset; // Offset for firing arrows

	/** Character Variables */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		int32 Level; // The current level of the player

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		float MaxHealth; // Base health amount, increases over time and depletes when hit by an enemy

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		float Health; // Current health amount, increases over time and depletes when hit by an enemy

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		float HealthRegen; // How much health is regained a second (tick);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		float Stamina; // Base Stamina amount, increases over time and depletes on attacks/special attacks

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		float StaminaRegen; // How much stamina is regained a second (tick);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		float MovementSpeed; // The current Movement speed of the player as a percentage

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		float AttackSpeed; // How fast the player strikes with basic attacks as a percentage

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		float AttackCD; // How fast the player strikes with basic attacks as a percentage

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		float CritChance; // The percentage chance that the player has to critically hit

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		float CritMultiplier; // How much damage a critical hit does as a multiplier

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		float DamageMin; // Base damage minimum amount

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		float DamageMax; // Base damage maximum amount

	/** Projectile class to spawn when OnFire is called */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	class AWeaponBase*  WeaponInst;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		TSubclassOf<class AWeaponBase>  WeaponClass;

	UFUNCTION(BlueprintImplementableEvent, Category = Fire)
		void OnFire();

	/** Player Functions / Events */
	/** Cause a hit event on the selected enemy */
	UFUNCTION(BlueprintCallable, Category = Util)
		bool HitEnemy(AAGPCharacter * Enemy);

	/** Edit the player's health value */
	UFUNCTION(BlueprintCallable, Category = Util)
		void  AppendHealth(float amount);

	/** Take the given amount of damage from the character's HP */
	UFUNCTION(BlueprintImplementableEvent, Category = Health)
		void OnTakeDamage(float amount);

	/** Add the given amount of health to the character's HP */
	UFUNCTION(BlueprintImplementableEvent, Category = Health)
		void OnGiveHealth(float amount);

	/** Get Weapon type based on class */
	UFUNCTION(BlueprintCallable, Category = Weapon)
		int32 GetWeaponType(AWeaponBase * Weapon);

	/** Instantly kill the character*/
	UFUNCTION(BlueprintCallable, Category = Health)
		void KillCharacter();

	/**  */
	UFUNCTION(BlueprintImplementableEvent, Category = Health)
		void OnDeath();

	UFUNCTION(BlueprintImplementableEvent, Category = Health)
		void PlayBegin();

	virtual void Die(AAGPCharacter * Killer);

	/** Sets the default values for all player variables above */
	void SetCharacterVariables();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
	bool bPlayWeaponSound;

	/** spawn inventory, setup initial variables */
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
};
