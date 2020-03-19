// Fill out your copyright notice in the Description page of Project Settings.

#include "AGP.h"
#include "MeleeWeaponBase.h"
#include "DungeonBase.h"
#include "InteractableBase.h"
#include "PlayerCharacter.h"
#include "AICharacter.h"

AMeleeWeaponBase::AMeleeWeaponBase(const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer) {

}

void AMeleeWeaponBase::Attack(AAGPCharacter* User){
	const FVector FaceLocation = User->GetActorForwardVector();

	AAGPCharacter * Character = Cast<AAGPCharacter>(User);
	if (Character != NULL) {
		TArray<AActor *> AttackActors;
		Character->WeaponReachSphere->GetOverlappingActors(AttackActors);

		for (AActor * Actor : AttackActors) {
			if (Actor == User) continue;
			ADungeonBase * room = Cast<ADungeonBase>(Actor); if (room != NULL){ continue; }


			const FVector ActorDirection = (Actor->GetActorLocation() - Character->GetActorLocation()).GetSafeNormal();
			if (FVector::DotProduct(FaceLocation, ActorDirection) < 0.0f) continue;

			// If the Actor is in range of the player and is "hit" by the attack.
			AInteractableBase * obj = Cast<AInteractableBase>(Actor); if (obj != NULL){ 
				if (obj->InteractableType == 1){
					obj->OnInteract(User);
				}
			}
			// If a player hits the AI
			APlayerCharacter * chr = Cast<APlayerCharacter>(User);
			AAICharacter * ai = Cast<AAICharacter>(Actor);
			if (chr != NULL && ai != NULL){
				float damage = FMath::RandRange(chr->DamageMin, chr->DamageMax) * -1;
				ai->AppendHealth(damage);
				chr->DamageDone = chr->DamageDone + (damage *-1);
				if (ai->Health <= 0){
					ai->Die(chr);
				}
			}

			// If an AI hits a player
			APlayerCharacter * ply = Cast<APlayerCharacter>(Actor);
			AAICharacter * enemyai = Cast<AAICharacter>(User);
			if (ply != NULL && enemyai != NULL){
				float damage = FMath::RandRange(enemyai->DamageMin, enemyai->DamageMax) * -1;
				ply->AppendHealth(damage);
				ply->DamageTaken = ply->DamageTaken + (damage *-1);
				if (ply ->Health <= 0){
					ply->Die(enemyai);
				}
			}
		}
	}
	User->OnFire();
}


