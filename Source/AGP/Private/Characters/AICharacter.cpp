// Fill out your copyright notice in the Description page of Project Settings.

#include "AGP.h"
#include "AICharacter.h"
#include "PlayerCharacter.h"


AAICharacter::AAICharacter(const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer) {
	XPvalue = (Level * (55 + Level));
}

void AAICharacter::AttackAttempt(){
	if (WeaponClass != NULL) {
		UWorld * const World = GetWorld();
		if (World != NULL) {
			ARangedWeaponBase * RWep = Cast<ARangedWeaponBase>(WeaponInst);
			if (RWep){ // If the weapon is ranged				
				RWep->OnAttack(this);
			}
			else{
				AMeleeWeaponBase * MWep = Cast<AMeleeWeaponBase>(WeaponInst);
				if (MWep){ // If the weapon is melee
					WeaponReachSphere->SetSphereRadius(MWep->weaponReach);
					MWep->OnAttack(this);
				}
				else{ ScreenInfo(TEXT("Weapon cast failed")); }
			}
		}
	}
}

void AAICharacter::Die(AAGPCharacter * Killer){
	WeaponActor->DestroyComponent();
	WeaponInst->DestroyWeapon();
	Destroy();
	//GetWorld()->ForceGarbageCollection(true);

	APlayerCharacter * chr = Cast<APlayerCharacter>(Killer);
	if (chr != NULL){
		chr->KillEnemy(this);
	}
}

void AAICharacter::BeginPlay(){
	Super::BeginPlay();

	TArray<AActor *> players;
	UGameplayStatics::GetAllActorsOfClass(this, APlayerCharacter::StaticClass(), players);

	if (players.Num() > 0){
		if (players[0] == NULL){
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::White, TEXT("BROKE"));
		}
		else{
			APlayerCharacter * ply = Cast<APlayerCharacter>(players[0]);
			for (int i = 0; i < ply->Level; i++){
				LevelUp();
			}
		}
	}
}

void AAICharacter::LevelUp(){
	Level++;
	DamageMin = DamageMin + (Level);
	DamageMax = DamageMax + (Level);
	MaxHealth = MaxHealth + (Level * 5);
	Health = MaxHealth;
	HealthRegen = (Level * Level);
	MovementSpeed = MovementSpeed + (Level * 0.1);
	AttackSpeed = AttackSpeed + (Level * 0.2);
	CritChance = CritChance + (Level * 0.05f);
	CritMultiplier = CritMultiplier + (Level * 0.01);
	XPvalue = (Level * ((55 / (Level/2) + Level)));
}
