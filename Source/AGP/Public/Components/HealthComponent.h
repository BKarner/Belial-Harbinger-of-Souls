// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class AGP_API UHealthComponent : public UActorComponent {
    GENERATED_BODY()

    protected:
        float HealTime = 0.0f;

    public:
        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health|Settings")
        float HealAmount = 1.0f;

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health|Settings")
        float HealFrequency = 1.0f;

        // Sets default values for this component's properties
        UHealthComponent();

        // Called when the game starts
        virtual void InitializeComponent() override;

        // Called every frame
        virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
