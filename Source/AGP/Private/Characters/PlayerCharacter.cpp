// Fill out your copyright notice in the Description page of Project Settings.

#include "AGP.h"
#include "AICharacter.h"
#include "ScreenTextManager.h"
#include "PlayerCharacter.h"



APlayerCharacter::APlayerCharacter(const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer) {
	/** Creates a camera boom and attaches it to the character, this will be used to rotate and move the camera smoothly  */
	CameraBoom = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, -100.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	/** Creates the camera component and attaches it to the boom, and stops it from rotating the same way as the camera boom */
	CameraComponent = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("TopDownCamera"));
	CameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	XP = 0.0f;
	XPreq = (((5 * Level) + 5)*(45 + (2 * Level)));
}

void APlayerCharacter::OnFire() {
	if (WeaponClass != NULL) {
		UWorld * const World = GetWorld();
		if (World != NULL) {
			ARangedWeaponBase * RWep = Cast<ARangedWeaponBase>(WeaponInst);
			if (RWep){ // If the weapon is ranged
				RWep->OnAttack(this);
			}
			else{
				AMeleeWeaponBase * MWep = Cast<AMeleeWeaponBase>(WeaponInst);
				if (MWep){ // If the weapon is melee
					WeaponReachSphere->SetSphereRadius(MWep->weaponReach);
					MWep->OnAttack(this);
				}
				else{ ScreenInfo(TEXT("Weapon cast failed")); }
			}
		}
		AttackCD = AttackSpeed;
	}
}

void APlayerCharacter::KillEnemy(AAGPCharacter * Enemy){
	AAICharacter * aienemy = Cast<AAICharacter>(Enemy);
	if (aienemy != NULL){
		GiveXP(aienemy->XPvalue);
	}
}

void APlayerCharacter::GiveXP(float amount){
	XP = XP += amount;
	FScreenText XPText;
	XPText.OutlineColour = FColor::Black;
	XPText.Scale = 0.5f;
	XPText.Position = GetActorLocation();
	XPText.Velocity = FVector(500.0f, 0.0f, 0.0f);

	const FVector Direction = FMath::VRandCone(FVector(0.0f, 1.0f, 0.0f), PI * 0.5f);
	XPText.Acceleration = Direction * (FMath::RandHelper(50) > 25 ? -1.0f : 1.0f) * 250.0f;
	XPText.Acceleration.X = -1000.0f;

	XPText.Colour = FColor::Blue;
	XPText.Text = FString("+") + FString::SanitizeFloat(amount) + FString(" xp");
	ScreenTextManager::AddText(XPText);
	if (XP >= XPreq){
		LevelUp();
	}
}

void APlayerCharacter::LevelUp(){
	XP -= XPreq; Level++;
	if (XP <= 0){ XP = 0; }
	XPreq = (((5 * Level) + 5)*(45 + (2 * Level)));

	DamageMin = DamageMin + (Level + 15);
	DamageMax = DamageMax + (Level + 15);
	MaxHealth = MaxHealth + (Level * 15);
	Health = MaxHealth;
	HealthRegen = (Level * Level / 2);
	MovementSpeed = MovementSpeed + (Level * 0.1);
	CritChance = CritChance + (Level * 0.05f);
	CritMultiplier = CritMultiplier + (Level * 0.01);

	FScreenText LevelText;
	LevelText.OutlineColour = FColor::Black;
	LevelText.Scale = 1.5f;
	LevelText.Position = GetActorLocation();
	LevelText.Velocity = FVector(500.0f, 0.0f, 0.0f);

	const FVector Direction = FMath::VRandCone(FVector(0.0f, 1.0f, 0.0f), PI * 0.5f);
	LevelText.Acceleration = Direction * (FMath::RandHelper(50) > 25 ? -1.0f : 1.0f) * 250.0f;
	LevelText.Acceleration.X = -1000.0f;

	LevelText.Colour = FColor::Yellow;
	LevelText.Text = FString("LEVEL UP!");
	LevelText.Lifetime = 1.0f;
	ScreenTextManager::AddText(LevelText);
}

void APlayerCharacter::Die(AAGPCharacter * Killer){
}

void APlayerCharacter::BeginPlay(){
	Super::BeginPlay();
	UpdateStats();
}

void APlayerCharacter::UpdateStats(){
	int templevel = 0;
	while (templevel != Level){
		DamageMin += (templevel + 15);
		DamageMax = DamageMax + (templevel + 15);
		MaxHealth = MaxHealth + (templevel * 20);
		Health = MaxHealth;
		HealthRegen = (templevel * templevel / 2);
		MovementSpeed = MovementSpeed + (templevel * 0.1);
		CritChance = CritChance + (templevel * 0.05f);
		CritMultiplier = CritMultiplier + (templevel * 0.01);
		templevel++;
	}

	XP -= XPreq;
	if (XP <= 0){ XP = 0; }
	XPreq = (((5 * Level) + 5)*(45 + (2 * Level)));
}