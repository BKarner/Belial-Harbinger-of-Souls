// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "LessDamageComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AGP_API ULessDamageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Less Damage|Component")
    float LessDamageAmount = 10.0f;
	// Sets default values for this component's properties
	ULessDamageComponent();

	// Called when the game starts
	virtual void InitializeComponent() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

		
	
};
