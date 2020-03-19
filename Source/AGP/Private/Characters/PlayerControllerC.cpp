// Fill out your copyright notice in the Description page of Project Settings.

#include "AGP.h"
#include "PlayerControllerC.h"
#include "InteractableBase.h"


APlayerControllerC::APlayerControllerC(const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer) {
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;

	bEnableMouseOverEvents = true;

	/** Variable defaults */
	bIsMouseBeingHeld = false;
}

void APlayerControllerC::SetupInputComponent(){
	Super::SetupInputComponent();

	/** Bind Input to Input delegates */
	InputComponent->BindAction("Move", IE_Pressed, this, &APlayerControllerC::MouseOn);
	InputComponent->BindAction("Move", IE_Released, this, &APlayerControllerC::MouseOff);
	InputComponent->BindAction("StandAttack", IE_Pressed, this, &APlayerControllerC::StandAttack);
	InputComponent->BindAction("Fire", IE_Pressed, this, &APlayerControllerC::OnFire);
	InputComponent->BindAction("Debug", IE_Pressed, this, &APlayerControllerC::Debug);
}

void APlayerControllerC::Debug(){
	APlayerCharacter * const Pawn = static_cast<APlayerCharacter*>(GetPawn());
	if (Pawn != NULL){
		Pawn->DebugUI = !Pawn->DebugUI;
	}
}

void APlayerControllerC::PlayerTick(float DeltaTime){
	Super::PlayerTick(DeltaTime);

	/** If the mouse is being held, constantly update the new position */
	if (bIsMouseBeingHeld == true){
		MoveInMouseDirection();
	}

}

void APlayerControllerC::OnFire() {
	APlayerCharacter * const Pawn = static_cast<APlayerCharacter*>(GetPawn());
	Pawn->OnFire();
}

void APlayerControllerC::StandAttack(){
	/** Conenct the pawn to the player's character */
	APlayerCharacter * const Pawn = static_cast<APlayerCharacter*>(GetPawn());

	if (Pawn){
		if (Pawn->AttackCD <= 0.0f){
			FHitResult Mousehit;
			/** Get the world position of the mouse click */
			GetHitResultUnderCursorByChannel(TraceTypeQuery_MAX, true, Mousehit);

			/** Calculates the Direction of the mouse location */
			const FVector Direction = (Mousehit.ImpactPoint - Pawn->GetActorLocation()).GetClampedToMaxSize(1.0f);

			/** Limit the rotation to the YAW rotation and set the player's rotation to it */
			FRotator Rotation = Direction.Rotation(); Rotation.Pitch = 0; Rotation.Roll = 0;
			Pawn->SetActorRotation(Rotation);
			Pawn->GetMovementComponent()->StopActiveMovement();
			Pawn->OnFire();
		}
	}
}

void APlayerControllerC::MoveInMouseDirection() {
	FHitResult Mousehit;
	/** Get the world position of the mouse click */
	GetHitResultUnderCursorByChannel(TraceTypeQuery_MAX, true, Mousehit);

	/** Connect the pawn to the player's character */
	APawn* const Pawn = GetPawn();
	/** Make sure there is a character, if there is and something in the world is clicked then continue */
	if (Pawn && Mousehit.bBlockingHit) {
		const UWorld * World = GetWorld();
		if (World != NULL) {
			/** Calculates the Direction and Distance of the player to the mouse location */
			FHitResult Tracehit;
			const FVector pLoc = Pawn->GetActorLocation();
			FVector Target = Mousehit.ImpactPoint;
			const FVector Direction = (Target - pLoc).GetClampedToMaxSize(1.0f);
			const float Distance = FMath::CeilToFloat(FVector::Dist(Target, pLoc));

			/** Set the parameters for the line trace */
			FCollisionQueryParams p; {
				p.bTraceComplex = true; 
				p.bTraceAsyncScene = true;
				p.AddIgnoredActor(Pawn);
			}

			/** Performs the line trace from the player to the mouse button and checks to see if a wall is in the way. */
			const FVector End = pLoc + (Direction * Distance);

			/** If a wall is in the way then set the destination to the closest point to the obstructing wall in the direction of the mouse button */
			bool HasHit = World->LineTraceSingle(Tracehit, pLoc, End, ECC_MAX, p);

			const UNavigationSystem * NavSys = World->GetNavigationSystem();
			if (NavSys != NULL) {
				/** Move the player to the location. If the hit is blocked move to blocked location; if not, move to the mouse location */
				NavSys->SimpleMoveToLocation(this, (Tracehit.bBlockingHit ? Tracehit.ImpactPoint : End));
			}

			return;
		}
	}
}

/** Miscellaneous Input Delegates */
void APlayerControllerC::MouseOn(){
	FHitResult Mousehit;
	/** Get the world position of the mouse click */
	GetHitResultUnderCursorByChannel(TraceTypeQuery_MAX, true, Mousehit);

	/** Connect the pawn to the player's character */
	APawn* const Pawn = GetPawn();

	if (Mousehit.Actor != NULL){
		AInteractableBase* io = Cast<AInteractableBase>(Mousehit.GetActor());
		if (io != NULL){
			if (FVector::Dist(Pawn->GetActorLocation(), io->GetActorLocation()) <= 200.0f){
				ACharacter * Char = Cast<ACharacter>(Pawn);
				io->OnInteract(Char);
			} else {
				bIsMouseBeingHeld = true;
			}
		} else{
			bIsMouseBeingHeld = true;
		}
	}
}

void APlayerControllerC::MouseOff(){
	bIsMouseBeingHeld = false;
}