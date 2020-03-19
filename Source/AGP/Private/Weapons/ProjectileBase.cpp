// Fill out your copyright notice in the Description page of Project Settings.

#include "AGP.h"
#include "AGPCharacter.h"
#include "PlayerCharacter.h"
#include "AICharacter.h"
#include "ProjectileBase.h"
#include "InteractableBase.h"
#include "GameFramework/ProjectileMovementComponent.h"


AProjectileBase::AProjectileBase(const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer) {

	// use sphere for collisions
	CollisionComp = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(10.0f); // set size of sphere
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
	RootComponent = CollisionComp;

	// set up projectiles movement
	ProjectileMovement = ObjectInitializer.CreateDefaultSubobject<UProjectileMovementComponent>(this, TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;

	// Destroy the projectile after alloted time
	InitialLifeSpan = 4.0f;
}

void AProjectileBase::OnHit(AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit) {
	AInteractableBase * obj = Cast<AInteractableBase>(OtherActor);
	if (obj != NULL && obj->InteractableType == 1){
		AAGPCharacter* chr = Cast<AAGPCharacter>(Owner);
		obj->OnInteract(chr);
		Destroy();
	}

	// If a player hits an AI
	if (Owner != NULL){
		APlayerCharacter * chr = Cast<APlayerCharacter>(Owner);
		AAICharacter * ai = Cast<AAICharacter>(OtherActor);
		if (chr != NULL && ai != NULL){
			float damage = FMath::RandRange(chr->DamageMin, chr->DamageMax) * -1;
			ai->AppendHealth(damage);
			chr->DamageDone = chr->DamageDone + (damage *-1);
			if (ai->Health <= 0){
				ai->Die(chr);
			}
			Destroy();
		}

		// If an AI hits a player
		APlayerCharacter * ply = Cast<APlayerCharacter>(OtherActor);
		AAICharacter * enemyai = Cast<AAICharacter>(Owner);
		if (ply != NULL && enemyai != NULL){
			float damage = FMath::RandRange(enemyai->DamageMin, enemyai->DamageMax) * -1;
			ply->AppendHealth(damage);
			ply->DamageTaken = ply->DamageTaken + (damage *-1);
			if (ply->Health <= 0){
				ply->Die(enemyai);
			}
			Destroy();
		}
		if (ply == NULL && enemyai != NULL){
			AAICharacter * ai = Cast<AAICharacter>(OtherActor);
			if (ai != NULL){
				Destroy();
			}
		}

		// If projectile hits a projectile
		AProjectileBase * proj = Cast<AProjectileBase>(OtherActor);
		if (proj != NULL){
			Destroy();
			proj->Destroy();
		}
			
	}
	
	UParticleSystemComponent* particlesys = FindComponentByClass<UParticleSystemComponent>();
	if (particlesys != NULL){
		particlesys->CustomTimeDilation = 1.0f;
	}

}

