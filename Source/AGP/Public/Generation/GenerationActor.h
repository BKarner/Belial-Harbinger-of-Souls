// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DungeonBase.h"
#include "DungeonDoorway.h"
#include "GenerationActor.generated.h"

/**
 * 
 */
UCLASS()
class AGP_API AGenerationActor : public AActor{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon")
	TSubclassOf<class ADungeonBase> EntranceRoomClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon")
	TSubclassOf<class ADungeonBase> ExitRoomClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dungeon")
	ADungeonBase * EntranceRoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dungeon")
	ADungeonBase * ExitRoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon")
		TArray<TSubclassOf<class ADungeonBase>> DungeonRoomClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon")
		TArray<TSubclassOf<class ADungeonBase>> DungeonCorridorClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon")
		int32 MaxNumOfRooms;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon")
		int32 NumOfRooms;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon")
		int32 MinNumOfRooms;

	UFUNCTION(BlueprintCallable, Category = "Generation")
		void GenerateDungeon();

	float getOppositeAngle(float ang){
		return ang + 180;

	}

	UFUNCTION(BlueprintImplementableEvent, Category = "Generation")
		void GenerationEnded();

	AGenerationActor(const FObjectInitializer & ObjectInitializer);

	bool bRoomCycle = false;
	bool bGenerationInProgress = false;

	void ResetDungeon();
	void DeleteDungeon();
	void InitDungeonGeneration();
	void AddRemainingDoors();
	void CloseDungeonDoors();
	void GenerateEndRoom();
	void GenerateRoomContents();

	TArray<ADungeonBase *> AllRooms;
	TArray<ADungeonBase *> ToGenerateFrom;
	TArray<ADungeonBase *> ToGenerateFromPlaceHolder;

	TArray<UDungeonDoorway *> AllDoors;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
};
