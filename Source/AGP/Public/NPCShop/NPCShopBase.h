// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "NPCShopBase.generated.h"

UCLASS()
class AGP_API ANPCShopBase : public AActor
{
	GENERATED_BODY()
    protected: 

    public:
        UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPCShop|Components")
        USceneComponent * SceneComponent;

        UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPCShop|Components")
        UStaticMeshComponent * Mesh;

        UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPCShop|Trigger Area")
        UBoxComponent * TriggerVolume;

	    // Sets default values for this actor's properties
        ANPCShopBase(const FObjectInitializer & ObjectInitializer = FObjectInitializer::Get());

        UFUNCTION()
        void OnBoxOverlap(AActor * OtherActor, class UPrimitiveComponent * OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);


	    // Called when the game starts or when spawned
	    virtual void BeginPlay() override;
	
	    // Called every frame
	    virtual void Tick( float DeltaSeconds ) override;
        
	
	
};
