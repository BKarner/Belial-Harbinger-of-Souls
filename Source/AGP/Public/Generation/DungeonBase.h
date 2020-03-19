// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DungeonBase.generated.h"

/**
 * 
 */
UCLASS()
class AGP_API ADungeonBase : public AActor{
	GENERATED_UCLASS_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scene")
		USceneComponent * SceneComponent;

	void PrepareDestroy();
	void GenerateContents();

protected:
	virtual void BeginPlay() override;
	
};
