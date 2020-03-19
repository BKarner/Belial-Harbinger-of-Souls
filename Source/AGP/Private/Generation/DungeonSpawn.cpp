// Fill out your copyright notice in the Description page of Project Settings.

#include "AGP.h"
#include "DungeonSpawn.h"

UDungeonSpawn::UDungeonSpawn(const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer) {
	billboard = ObjectInitializer.CreateDefaultSubobject<UBillboardComponent>(this, TEXT("Billboard"));
	billboard->AttachTo(this);
}

void UDungeonSpawn::InitSpawn(){
	switch (Type){
		case ETypeEnum::PICKUP_SPAWN:{
			int index = FMath::RandRange(0, spawnablePickups.Num()-1);
			SpawnedObject = GetWorld()->SpawnActor<APickupBase>(spawnablePickups[index], GetComponentLocation(), GetComponentRotation());
			AppendAttributes(Type);
			break;
		}
		case ETypeEnum::ENEMY_SPAWN:{
			int index = FMath::RandRange(0, spawnableEnemies.Num() - 1);
			FVector loc = GetComponentLocation();
			loc.Z += 80.0f;
			SpawnedObject = GetWorld()->SpawnActor<AAICharacter>(spawnableEnemies[index], loc, GetComponentRotation());
			AppendAttributes(Type);
			break;
		}
		case ETypeEnum::MISC_SPAWN:{
			break;
		}
		case ETypeEnum::ALL_SPAWN:{
			break;
		}
	}
}

void UDungeonSpawn::AppendAttributes(ETypeEnum type){
	APickupBase* pickup_obj = Cast<APickupBase>(SpawnedObject);
	if (pickup_obj != NULL){

	}

	AAICharacter* AI_obj = Cast<AAICharacter>(SpawnedObject);
	if (AI_obj != NULL){
		AI_obj->SpawnDefaultController();
	}

	/** Add Lootable objects? */
}