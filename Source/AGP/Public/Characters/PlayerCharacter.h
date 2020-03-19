// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AGPCharacter.h"
#include "PlayerCharacter.generated.h"

UENUM(BlueprintType)
namespace EPlayerType {
    enum Type {
        PT_Brute					UMETA(DisplayName = "Brute"),
        PT_RangeGirl				UMETA(DisplayName = "Range Girl")
    };
}

/**
 *
 */
UCLASS()
class AGP_API APlayerCharacter : public AAGPCharacter {
    GENERATED_UCLASS_BODY()

    public:
        /** Character components */
        /** Top down camera */
        UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
        class UCameraComponent * CameraComponent;

        /** Camera boom positioning the camera above the character */
        UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
        class USpringArmComponent * CameraBoom;

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
        TEnumAsByte<EPlayerType::Type> PlayerType = EPlayerType::PT_Brute;

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
        int32 Kills; // Increments when the player kills an enemy or is responsible for an enemies death

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
        int32 Deaths; // Increments when the player dies / respawns

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
        float XP; // The current XP that they player has

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
        float XPreq; // The current XP that they player has



        UFUNCTION(BlueprintCallable, Category = Health)
        void KillEnemy(AAGPCharacter * Enemy);

        UFUNCTION(BlueprintCallable, Category = XP)
        void GiveXP(float amount);

        UFUNCTION(BlueprintCallable, Category = XP)
        void LevelUp();

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
        float Score;

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
        float DamageDone;

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
        float DamageTaken;

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
        float TimeBonus;

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
        bool DebugUI; // 

        /** Utility Functions */
        void OnFire();

        UFUNCTION(BlueprintCallable, Category = "Player")
        void UpdateStats();

        virtual void BeginPlay() override;
        virtual void Die(AAGPCharacter * Killer) override;
};
