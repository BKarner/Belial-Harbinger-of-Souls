// Fill out your copyright notice in the Description page of Project Settings.

#include "AGP.h"
#include "DungeonSpawn.h"
#include "DungeonBase.h"


ADungeonBase::ADungeonBase(const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer) {
	SceneComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("SceneComponent"));
	RootComponent = SceneComponent;
}

void ADungeonBase::BeginPlay(){
	Super::BeginPlay();

	
}

void ADungeonBase::GenerateContents(){
	TArray<UDungeonSpawn *> Spawners;
	GetComponents(Spawners);

	for (int i = 0; i < Spawners.Num(); i++){
		Spawners[i]->InitSpawn();
	}
}

void ADungeonBase::PrepareDestroy(){
	TArray<UDungeonSpawn *> Spawners;
	GetComponents(Spawners);

	if (Spawners.Num() > 0){
		for (int i = 0; i < Spawners.Num(); i++){
			if (Spawners[i] != NULL){
				if (Spawners[i]->SpawnedObject != NULL){
					Spawners[i]->SpawnedObject->Destroy();
				}
			}
		}
	}
	Destroy();
}

