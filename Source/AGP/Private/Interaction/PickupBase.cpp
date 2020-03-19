// Fill out your copyright notice in the Description page of Project Settings.

#include "AGP.h"
#include "PickupBase.h"

APickupBase::APickupBase(const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer){
	PrimaryActorTick.bCanEverTick = true;

	doesBob = doesRotate = true;
	PickedUpBy = NULL;
	isPickedUp = false;
	bobRate = 5.0f;
	bobAmount = 0.5f;
	pickupRate = 1.0f;
	pickupRange = 200.0f;

	Scene = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Scene"));
	RootComponent = Scene;

	pickupSphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("PickupRangeSphere"));
	pickupSphere->AttachTo(RootComponent);
	pickupSphere->SetSphereRadius(pickupRange);

	OnActorBeginOverlap.AddDynamic(this, &APickupBase::OnOverlap);
}

void APickupBase::OnOverlap(AActor * otherActor){
	APlayerCharacter * chr = Cast<APlayerCharacter>(otherActor);
	if (chr != NULL){
		OnPickupPickup(chr);
	}
}

bool APickupBase::MoveTowardsPlayer(float DeltaSeconds){
	float elapsedTimeTemp = 0.0f;
	elapsedTimeTemp += DeltaSeconds;
	FVector pos = GetActorLocation(); 
	float Distance = FVector::Dist(pos, PickedUpBy->GetActorLocation());
	if (Distance <= 50.0f){ return true; }
	
	FVector Direction = PickedUpBy->GetActorLocation() - pos;
	pos = FMath::VInterpTo(pos, PickedUpBy->GetActorLocation(), DeltaSeconds * pickupRate, 2.0f);
	SetActorLocation(pos);
	return false;
}

void APickupBase::BobAndRotate(float DeltaSeconds){
	float elapsedTimeTemp = elapsedTime;
	elapsedTime += DeltaSeconds;
	elapsedTimeTemp += (DeltaSeconds * bobRate);
	if (doesBob){
		float z = FMath::Sin(elapsedTimeTemp) * bobAmount;
		FVector newpos = GetActorLocation(); 
		newpos.Z += z;
		SetActorLocation(newpos);
	}
	if (doesRotate){
		FRotator rot = GetActorRotation();
		rot = rot += FRotator(0.0f, 1.0f, 0.0f);
		SetActorRotation(rot);
	}
}