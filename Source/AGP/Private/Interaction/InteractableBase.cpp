// Fill out your copyright notice in the Description page of Project Settings.

#include "AGP.h"
#include "InteractableBase.h"


AInteractableBase::AInteractableBase(const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer) {
	Scene = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Scene"));
	RootComponent = Scene;

	Mesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Mesh"));
	Mesh->AttachTo(Scene);

	Dest_Mesh = ObjectInitializer.CreateDefaultSubobject<UDestructibleComponent>(this, TEXT("Dest Mesh"));
	Dest_Mesh->AttachTo(Scene);
	Dest_Mesh->SetVisibility(true);

	PrimaryActorTick.bCanEverTick = true;

	OutlineCol = OUTLINE_DEFAULT;
}

void AInteractableBase::OnTick(float DeltaSeconds){

}

void AInteractableBase::SetDefaultColours() {
	if (OutlineCol == OUTLINE_DEFAULT) {
		switch (InteractableType) {
			case 1:{ // IO_DESTRUCTING
				OutlineCol = OUTLINE_DESTRUCTABLE;
				break;
			}case 2:{ // IO_MOVING
					   break;
			}case 3:{ // IO_OPENING
				break;
			}
			default:{ // IO_DEFAULT
				OutlineCol = OUTLINE_DEFAULT;
				break;
			}
		}
	}
}

void AInteractableBase::OnInteract(ACharacter * User){
	switch (InteractableType){
		case 1:{ // IO_DESTRUCTING
			Mesh->SetCanEverAffectNavigation(false);
			Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			Mesh->SetStaticMesh(NULL);

			if (Dest_Mesh != NULL){
				FVector ForceDirection;
				ForceDirection = GetActorLocation() - User->GetActorLocation();
				ForceDirection.Z = 1.0f;
				Dest_Mesh->ApplyDamage(1.0f, Dest_Mesh->GetComponentLocation(), ForceDirection, 5000.0f);
			}
			break;
		}case 2:{ // IO_MOVING
			break;
		}case 3:{ // IO_OPENING
			break;
		}
		default:{ // IO_DEFAULT
			break;
		}
	}
	OnInteracted(User);
}

void AInteractableBase::OnBeginCursorOver(){
	bIsMouseOver = true;
	Mesh->SetRenderCustomDepth(true);
}

void AInteractableBase::OnEndCursorOver(){
	bIsMouseOver = false;
	Mesh->SetRenderCustomDepth(false);
}


