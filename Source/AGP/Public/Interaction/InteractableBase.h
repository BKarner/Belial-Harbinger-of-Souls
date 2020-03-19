// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "InteractableBase.generated.h"

/**
 * 
 */
UENUM()
namespace EInteractableTypes {
	enum Type {
		IO_DEFAULT					UMETA(DisplayName = "Default"),
		IO_DESTRUCTING				UMETA(DisplayName = "Destructing"),
		IO_MOVING					UMETA(DisplayName = "Moving"),
		IO_OPENING					UMETA(DisplayName = "Opening")
	};
}

UCLASS()
class AGP_API AInteractableBase : public AActor{
	GENERATED_UCLASS_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MESH")
	class USceneComponent * Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MESH")
	class UStaticMeshComponent * Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MESH")
	class UDestructibleComponent * Dest_Mesh;

	/** The colour of the outline the interactable has */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "INTERACTABLE")
	FLinearColor OutlineCol;

	/** The type of object the interactable is */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "INTERACTABLE")
	TEnumAsByte<EInteractableTypes::Type> InteractableType;

	/** Boolean variable to hold whether the mouse is over the object */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "INTERACTABLE")
	bool bIsMouseOver;

	/** Called when the mouse is placed over the object */
	UFUNCTION(BlueprintCallable, Category = "INTERACTABLE")
	void OnBeginCursorOver();

	/** Called when the mouse is no longer over the object */
	UFUNCTION(BlueprintCallable, Category = "INTERACTABLE")
	void OnEndCursorOver();

	/** Called every frame update */
	UFUNCTION(BlueprintCallable, Category = "INTERACTABLE")
	void OnTick(float DeltaSeconds);

	/** Set default outline colours */
	UFUNCTION(BlueprintCallable, Category = "INTERACTABLE")
	void SetDefaultColours();

	UFUNCTION(BlueprintImplementableEvent, Category = "INTERACTABLE")
	void OnInteracted(ACharacter * User);

	void OnInteract(ACharacter * User);
};
