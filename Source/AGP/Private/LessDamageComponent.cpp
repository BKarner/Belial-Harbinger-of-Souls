// Fill out your copyright notice in the Description page of Project Settings.

#include "AGP.h"
#include "AGPCharacter.h"

#include "LessDamageComponent.h"


// Sets default values for this component's properties
ULessDamageComponent::ULessDamageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULessDamageComponent::InitializeComponent()
{
	Super::InitializeComponent();

    AActor * OwningActor = GetOwner();
    AAGPCharacter * MyPlayer = (OwningActor != NULL ? Cast<AAGPCharacter>(OwningActor) : NULL);

    if (MyPlayer != NULL) {
        MyPlayer->OnTakeDamage(LessDamageAmount);
    }
}


// Called every frame
void ULessDamageComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

