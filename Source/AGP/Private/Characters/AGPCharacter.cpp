// Fill out your copyright notice in the Description page of Project Settings.

#include "AGP.h"
#include "AGPCharacter.h"
#include "ScreenTextManager.h"


AAGPCharacter::AAGPCharacter(const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer) {
    SetCharacterVariables();

    this->bSimGravityDisabled = true;
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    /** Keep the character's rotation smooth and fluent */
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
    GetCharacterMovement()->bConstrainToPlane = true;
    GetCharacterMovement()->bSnapToPlaneAtStart = true;

    WeaponActor = ObjectInitializer.CreateDefaultSubobject<UChildActorComponent>(this, TEXT("WeaponActor"));
    WeaponActor->AttachTo(this->GetMesh(), "hand_r", EAttachLocation::Type::SnapToTarget);

    /** */
    WeaponReachSphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("WeaponReachSphere"));
    WeaponReachSphere->AttachTo(RootComponent);
}

void AAGPCharacter::SetCharacterVariables() {
    // Health
    Health = 100.0f;
    HealthRegen = 1.0f;

    // Stamina
    Stamina = 125.0f;
    StaminaRegen = 0.0f;

    // Stats
    Level = 1;

    // Combat Stats
    MovementSpeed = 1.0f;
    AttackSpeed = 1.0f;
    CritChance = 0.15f;
    CritMultiplier = 0.1f;
    DamageMin = 20.0f;
    DamageMax = 30.0f;
}

bool AAGPCharacter::HitEnemy(AAGPCharacter * enemy) {
    return false;
}

void AAGPCharacter::AppendHealth(float amount) {
    if (amount == 0.0f || (Health + amount) > MaxHealth) { return; }

    FScreenText Damage;
    Damage.OutlineColour = FColor::Black;
    Damage.Scale = 1.0f;
    Damage.Position = GetActorLocation();
    Damage.Velocity = FVector(500.0f, 0.0f, 0.0f);

    const FVector Direction = FMath::VRandCone(FVector(0.0f, 1.0f, 0.0f), PI * 0.5f);
    Damage.Acceleration = Direction * (FMath::RandHelper(50) > 25 ? -1.0f : 1.0f) * 250.0f;
    Damage.Acceleration.X = -1000.0f;

    Health = FMath::Clamp(Health + amount, 0.0f, MaxHealth);

    if (amount <= 0.0f) {
        OnTakeDamage(amount -= 0.0f);
        Damage.Colour = FColor::Red;
		Damage.Text = FString::SanitizeFloat(amount);
		if (Health <= 0.0f) {
			OnDeath();
		}
    } else {
        OnGiveHealth(amount);
        Damage.Colour = FColor::Green;
        Damage.Text = FString("+") + FString::SanitizeFloat(amount);
    }
    ScreenTextManager::AddText(Damage);
}

int32 AAGPCharacter::GetWeaponType(AWeaponBase * Weapon) {
    if (Weapon == NULL) { return 0; } // 0 = None

    ARangedWeaponBase * RWep = Cast<ARangedWeaponBase>(Weapon);
    if (RWep != NULL) { return 1; } // 1 = Ranged

    AMeleeWeaponBase * MWep = Cast<AMeleeWeaponBase>(Weapon);
    if (MWep != NULL) { return 2; } // 2 = Melee
    return 0;
}

void AAGPCharacter::KillCharacter() {}
void AAGPCharacter::Die(AAGPCharacter * Killer) {}

void AAGPCharacter::PostInitializeComponents() {
    Super::PostInitializeComponents();
    FActorSpawnParameters SpawnInfo;
    SpawnInfo.bNoCollisionFail = true;
    WeaponInst = GetWorld()->SpawnActor<AWeaponBase>(WeaponClass, FVector(0.0f, 0.0f, -1500.0f), FRotator(0.0f, 0.0f, 0.0f), SpawnInfo);
}

void AAGPCharacter::BeginPlay() {
    Super::BeginPlay();
    PlayBegin();
}