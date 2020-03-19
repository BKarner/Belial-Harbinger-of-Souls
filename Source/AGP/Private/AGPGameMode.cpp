// Fill out your copyright notice in the Description page of Project Settings.

#include "AGP.h"
#include "AGPGameMode.h"
#include "ScreenTextManager.h"
#include "Kismet/GameplayStatics.h"

AAGPGameMode::AAGPGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer){

}

void AAGPGameMode::Tick(float DeltaSeconds){
	Super::Tick(DeltaSeconds);
	ScreenTextManager::Tick(DeltaSeconds);

}

void AAGPGameMode::Victory(){
	SetCurrentState(EAGPPlayState::EGameOver);
}

void AAGPGameMode::SetCurrentState(EAGPPlayState NewState) {
	CurrentState = NewState;

	HandleNewState(NewState);
}

void AAGPGameMode::HandleNewState(EAGPPlayState NewState){
	switch (NewState){
		case EAGPPlayState::EPlaying:{
			break;
		}
		case EAGPPlayState::EGameOver:{
			break;
		}
		case EAGPPlayState::EUnknown:{
			break;
		}
		default:{
			break;
		}
	}
}

void AAGPGameMode::BeginPlay() {
	Super::BeginPlay();

	SetCurrentState(EAGPPlayState::EPlaying);
}

