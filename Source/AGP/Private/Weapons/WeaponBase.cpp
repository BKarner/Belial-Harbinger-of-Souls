// Fill out your copyright notice in the Description page of Project Settings.

#include "AGP.h"
#include "WeaponBase.h"


AWeaponBase::AWeaponBase(const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer) {
	Scene = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Scene"));
	RootComponent = Scene;

	Mesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Mesh"));
	Mesh->AttachTo(Scene);
}

void AWeaponBase::DestroyWeapon(){
	Destroy();
}



