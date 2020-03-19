// Fill out your copyright notice in the Description page of Project Settings.

#include "AGP.h"
#include "RangedWeaponBase.h"
#include "AGPCharacter.h"


ARangedWeaponBase::ARangedWeaponBase(const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer) {

}

void ARangedWeaponBase::Attack(AAGPCharacter * User){
	UWorld * World = GetWorld();
	const FVector SpawnLocation = User->GetActorLocation() + (User->GetActorForwardVector() * 100.0f);
	AProjectileBase * proj = World->SpawnActor<AProjectileBase>(ProjectileClass, SpawnLocation, User->GetActorForwardVector().Rotation());
	proj->setOwner(User);
	User->OnFire();
}
