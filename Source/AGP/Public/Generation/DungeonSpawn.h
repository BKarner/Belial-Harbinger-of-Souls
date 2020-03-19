// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
#include "PickupBase.h"
#include "AICharacter.h"
#include "DungeonSpawn.generated.h"

/**
 * 
 */
UENUM()
enum class ETypeEnum : uint8{
	PICKUP_SPAWN		UMETA(DisplayName = "Pickup Spawner"),
	ENEMY_SPAWN			UMETA(DisplayName = "Enemy Spawner"),
	//LOOTABLE_SPAWN	UMETA(DisplayName = "Lootable Object Spawner"),
	//OBJECT_SPAWN		UMETA(DisplayName = "Object Spawner"),
	//LORE_SPAWN		UMETA(DisplayName = "Lore object Spawner"),
	MISC_SPAWN			UMETA(DisplayName = "Misc object Spawner"),
	ALL_SPAWN			UMETA(DisplayName = "Spawn random")
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class AGP_API UDungeonSpawn : public USceneComponent{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Billboard")
	UBillboardComponent * billboard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes, DisplayName = "Spawner Type")
	ETypeEnum Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes, DisplayName = "Spawnable Pickups")
	TArray<TSubclassOf<class APickupBase>> spawnablePickups;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes, DisplayName = "Spawnable Enemies")
	TArray<TSubclassOf<class AAICharacter>> spawnableEnemies;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes, DisplayName = "Spawnable Objects")
	//TArray<TSubclassOf<class AActor>> spawnableLootObjects;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes, DisplayName = "Spawnable Objects")
	//TArray<TSubclassOf<class AActor>> spawnableObjects;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes, DisplayName = "Spawnable Lore")
	//TArray<TSubClassOf<class AICharacter>> spawnableLore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes, DisplayName = "Spawnable Misc")
	TArray<TSubclassOf<class UObject>> spawnableMisc;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attributes)
	AActor * SpawnedObject;

	/** */

	UFUNCTION(BlueprintCallable, Category = "Spawner")
	void InitSpawn();

	UFUNCTION(BlueprintCallable, Category = "Spawner")
	void AppendAttributes(ETypeEnum ObjType);

protected:
	UDungeonSpawn(const FObjectInitializer & ObjectInitializer);
};
