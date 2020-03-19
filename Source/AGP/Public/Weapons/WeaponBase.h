// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

/**
 * 
 */
UCLASS()
class AGP_API AWeaponBase : public AActor{
	GENERATED_UCLASS_BODY()
	
	UFUNCTION(BlueprintImplementableEvent, Category = "WEAPON")
	void OnAttack(AAGPCharacter * User);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MESH")
		class USceneComponent * Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MESH")
		class UStaticMeshComponent * Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire")
		UAnimMontage * AnimToPlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		FVector LocalLocation; // Current health amount, increases over time and depletes when hit by an enemy

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		FVector LocalRotation; // How much health is regained a second (tick);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		FVector LocalScale; // How much health is regained a second (tick);

	void DestroyWeapon();
};
