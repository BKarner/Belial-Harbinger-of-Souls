// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "PlayerControllerC.h"
#include "AGPGameMode.generated.h"

/**
 * 
 */
UENUM(BlueprintType)

enum class EAGPPlayState : uint8 {

		EPlaying					UMETA(DisplayName = "Playing"),
		EGameOver					UMETA(DisplayName = "GameOver"),
		EUnknown					UMETA(DisplayName = "Default"),
};

UCLASS()
class AGP_API AAGPGameMode : public AGameMode{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, Category = "Game Conditions")
	void Victory();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GameConditions")
	EAGPPlayState CurrentState;

	EAGPPlayState GetCurrentState() const;

	void SetCurrentState(EAGPPlayState NewState);


	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

	void HandleNewState(EAGPPlayState NewState);
};

FORCEINLINE EAGPPlayState AAGPGameMode::GetCurrentState() const {
	return CurrentState;
}
