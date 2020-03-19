// Fill out your copyright notice in the Description page of Project Settings.

#include "AGP.h"

#include "PlayerControllerC.h"

#include "NPCShopBase.h"


// Sets default values
ANPCShopBase::ANPCShopBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    SceneComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Scene Component"));
    RootComponent = SceneComponent;

    Mesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Shop Mesh"));
    Mesh->AttachParent = RootComponent;
    Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    Mesh->RelativeLocation = FVector(0.0f, 0.0f, 0.0f);

    TriggerVolume = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("Open Shop Area"));
    TriggerVolume->AttachParent = RootComponent;
    TriggerVolume->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
    TriggerVolume->SetCollisionResponseToAllChannels(ECR_Overlap);
    TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ANPCShopBase::OnBoxOverlap);
    TriggerVolume->RelativeLocation = FVector(25.0f, 25.0f, 25.0f);


}

// Called when the game starts or when spawned
void ANPCShopBase::BeginPlay() {
    Super::BeginPlay();

}

// Called every frame
void ANPCShopBase::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);

}

void ANPCShopBase::OnBoxOverlap(AActor * OtherActor, class UPrimitiveComponent * OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {
}

