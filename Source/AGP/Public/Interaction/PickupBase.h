// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PlayerCharacter.h"
#include "PickupBase.generated.h"

/**
 * 
 */
UCLASS()
class AGP_API APickupBase : public AActor{
	GENERATED_BODY()

public:
	APickupBase(const FObjectInitializer & ObjectInitializer);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MESH")
	class USceneComponent * Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pickup)
	class USphereComponent * pickupSphere;

	UFUNCTION(BlueprintImplementableEvent, Category = "Pickup")
	void OnPickupPickup(APlayerCharacter * User);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		bool doesBob;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		float bobRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		float bobAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		bool doesRotate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		float rotateRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		APlayerCharacter * PickedUpBy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		bool isPickedUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		float pickupRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		float pickupRange;

protected:
	//virtual void Tick(float DeltaTime) override;
	float elapsedTime;

	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void OnOverlap(AActor * otherActor);

	UFUNCTION(BlueprintCallable, Category = "Pickup")
	bool MoveTowardsPlayer(float DeltaSeconds);

	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void BobAndRotate(float DeltaSeconds);
};