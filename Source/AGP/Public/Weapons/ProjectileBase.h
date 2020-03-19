// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

/**
*
*/
UCLASS()
class AGP_API AProjectileBase : public AActor {
	GENERATED_UCLASS_BODY()

		/** Sphere Collision Component.*/
		UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		class USphereComponent * CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
		class UProjectileMovementComponent * ProjectileMovement;

	/** The owner of the projectile */
	AActor * Owner;

	/** Called when projectile hits something */
	UFUNCTION()
		void OnHit(AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit);

	AActor* getOwner() { return Owner; }
	void setOwner(AActor * owner){ Owner = owner; }

};
