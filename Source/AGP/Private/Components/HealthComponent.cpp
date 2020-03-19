// Fill out your copyright notice in the Description page of Project Settings.

#include "AGP.h"
#include "AGPCharacter.h"
#include "HealthComponent.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent() {
    bWantsInitializeComponent = true;
    PrimaryComponentTick.bCanEverTick = true;
}



void UHealthComponent::InitializeComponent() {
    Super::InitializeComponent();
    HealTime = HealFrequency;
}



void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    HealTime -= DeltaTime;

    if (HealTime <= 0.0f) {
        HealTime = HealFrequency;

        AActor * OwningActor = GetOwner();
        AAGPCharacter * MyPlayer = (OwningActor != NULL ? Cast<AAGPCharacter>(OwningActor) : NULL);

        if (MyPlayer != NULL) {
            MyPlayer->AppendHealth(HealAmount);
        }
    }

}

