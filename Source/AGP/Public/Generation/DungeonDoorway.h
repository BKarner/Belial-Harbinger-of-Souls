// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DungeonDoorway.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UDungeonDoorway : public UStaticMeshComponent{
	GENERATED_UCLASS_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static Mesh")
	UStaticMesh * OpenMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static Mesh")
	UStaticMesh * ClosedMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Billboard")
	UBillboardComponent * billboard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arrow")
	UArrowComponent * arrow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Doorway")
	bool bIsUsed = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Doorway")
	float halfDoorWidth;

	void SetOpen(bool open){
		if (open == true){
			SetStaticMesh(OpenMesh);
		}else{
			SetStaticMesh(ClosedMesh);
		}
	}

	/** Returns half way between the door frames  location in world space */
	UFUNCTION(BlueprintCallable, Category = "Doorway")
		FVector GetDoorwayHalfWidthVector();
};
