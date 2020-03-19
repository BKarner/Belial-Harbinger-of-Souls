// Fill out your copyright notice in the Description page of Project Settings.

#include "AGP.h"
#include "DungeonDoorway.h"
//
UDungeonDoorway::UDungeonDoorway(const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer) {
	halfDoorWidth = 200.0f;

	billboard = ObjectInitializer.CreateDefaultSubobject<UBillboardComponent>(this, TEXT("Billboard"));
	billboard->AttachTo(this);
	billboard->SetRelativeLocation(FVector(halfDoorWidth, 0.0f, 0.0f));

	arrow = ObjectInitializer.CreateDefaultSubobject<UArrowComponent>(this, TEXT("Arrow"));
	arrow->AttachTo(this);
	arrow->SetRelativeLocation(FVector(halfDoorWidth, 0.0f, 150.0f));
	arrow->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));
}

FVector UDungeonDoorway::GetDoorwayHalfWidthVector(){
	FVector newLoc;
	newLoc = this->GetComponentLocation();
	newLoc.X += halfDoorWidth;
	return newLoc;
}