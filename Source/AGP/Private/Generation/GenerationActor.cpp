// Fill out your copyright notice in the Description page of Project Settings.

#include "AGP.h"
#include "DungeonDoorway.h"
#include "GenerationActor.h"

AGenerationActor::AGenerationActor(const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer) {
	PrimaryActorTick.bCanEverTick = true;
	NumOfRooms = 0;
	MinNumOfRooms = 10;
	MaxNumOfRooms = 20;
}

void AGenerationActor::InitDungeonGeneration() {
	EntranceRoom = GetWorld()->SpawnActor<ADungeonBase>(EntranceRoomClass, GetActorLocation(), FRotator(0.0f, 0.0f, 0.0f));
	
	AllRooms.Add(EntranceRoom);
	ToGenerateFrom.Add(EntranceRoom);

	bGenerationInProgress = true;
}

void AGenerationActor::ResetDungeon(){
	for (int i = 0; i < AllRooms.Num(); i++){
		AllRooms[i]->Destroy();
		if (EntranceRoom != NULL){
			EntranceRoom->Destroy();
		}
	}
	AllRooms.Empty();
	AllDoors.Empty();
	NumOfRooms = 0;
	InitDungeonGeneration();
}

void AGenerationActor::Tick(float DeltaSeconds){
	Super::Tick(DeltaSeconds);
	if (bGenerationInProgress == true){
		if (NumOfRooms < MinNumOfRooms){
			GenerateDungeon();
		}else{
			GenerateEndRoom();
			if (ExitRoom == NULL){
				ResetDungeon();
				return;
			}
			AddRemainingDoors();
			CloseDungeonDoors();
			GenerateRoomContents();
			bGenerationInProgress = false;
			GenerationEnded();
		}
	}
}

void AGenerationActor::AddRemainingDoors() {
	if (ToGenerateFrom.Num() > 0) {
		for (int i = 0; i < ToGenerateFrom.Num(); i++) {
			TArray<UDungeonDoorway *> roomExits;
			ToGenerateFrom[i]->GetComponents(roomExits);
			for (int b = 0; b < roomExits.Num(); b++) {
				AllDoors.Add(roomExits[b]);
			}
		}

	}
}

void AGenerationActor::GenerateRoomContents(){
	for (int i = 0; i < AllRooms.Num(); ++i){
		AllRooms[i]->GenerateContents();
	}
}

void AGenerationActor::BeginPlay(){
	Super::BeginPlay();
	InitDungeonGeneration();
}

void AGenerationActor::GenerateEndRoom(){
	int It = 0;
	It = AllDoors.Num() - 1;
	while(ExitRoom == NULL && It >= 0){
		if (AllDoors[It]->bIsUsed == true) {
			It--; 
			break;
		}
		ExitRoom = GetWorld()->SpawnActor<ADungeonBase>(ExitRoomClass, GetActorLocation(), FRotator(0.0f, 0.0f, 0.0f));

		TArray<UDungeonDoorway *> roomExits;
		ExitRoom->GetComponents(roomExits);

		UDungeonDoorway * connection; connection = roomExits[0];

		float entRot = connection->GetComponentRotation().Yaw;
		float exitRot = AllDoors[It]->GetComponentRotation().Yaw;

		float angDif = (getOppositeAngle(exitRot) - entRot);
		ExitRoom->SetActorRotation(FRotator(0.0f, angDif, 0.0f));

		FVector bOffset = ExitRoom->GetActorLocation() - connection->billboard->GetComponentLocation();
		ExitRoom->SetActorLocation(AllDoors[It]->billboard->GetComponentLocation() + bOffset);

		TArray<AActor *> OverlappingActors;
		ExitRoom->GetOverlappingActors(OverlappingActors);
		for (int8 b = 0; b < OverlappingActors.Num(); b++){
			ADungeonBase * isRoom = Cast<ADungeonBase>(OverlappingActors[b]);
			if (isRoom != NULL && isRoom != ExitRoom){
				GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::White, ExitRoom->GetActorLocation().ToString());
				//ExitRoom->PrepareDestroy();
				//ExitRoom = NULL;
				break;
			}
		}

		if (ExitRoom != NULL){
			FVector loc = ExitRoom->GetActorLocation();
			FRotator rot = ExitRoom->GetActorRotation();
			ExitRoom->PrepareDestroy();
			ExitRoom = GetWorld()->SpawnActor<ADungeonBase>(ExitRoomClass, loc, rot);

			AllDoors[It]->DestroyComponent();
			connection->DestroyComponent();
		}else{
			if (--It <= 0){
				break;
			}
		}
	}
}

void AGenerationActor::CloseDungeonDoors(){
	for (int i = 0; i < AllDoors.Num(); i++) {
		AllDoors[i]->SetOpen(false);
	}
}

void AGenerationActor::GenerateDungeon(){
	ADungeonBase * nextRoom; ADungeonBase * currentRoom;
	for (int i = 0; i < ToGenerateFrom.Num(); i++){
		currentRoom = ToGenerateFrom[i];

		TArray<UDungeonDoorway *> roomExits;
		currentRoom->GetComponents(roomExits);

		for (int i = 0; i < roomExits.Num(); i++) {
			AllDoors.Add(roomExits[i]);
			if (FMath::RandRange(0, 5) >= 4 || NumOfRooms >= MaxNumOfRooms) { 
				continue; 
			}
			bool bSuccess = false; int attempts = 5;
			TArray<UDungeonDoorway *> nextRoomExits;

			while (!bSuccess){
				if (attempts == 0){
					bSuccess = true;
					ToGenerateFromPlaceHolder.Remove(currentRoom);
					roomExits[i]->bIsUsed = false;
					break;
				}

				if (!bRoomCycle){
					// If a corridor is to be generated
					int ArrayIndex = FMath::RandRange(0, DungeonCorridorClasses.Num() - 1);

					nextRoom = GetWorld()->SpawnActor<ADungeonBase>(DungeonCorridorClasses[ArrayIndex], FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));
					nextRoom->GetComponents(nextRoomExits);
					int DoorIndex = FMath::RandRange(0, nextRoomExits.Num() - 1);
					UDungeonDoorway * connection; connection = nextRoomExits[DoorIndex];

					float entRot = connection->GetComponentRotation().Yaw;
					float exitRot = roomExits[i]->GetComponentRotation().Yaw;

					float angDif = (getOppositeAngle(exitRot) - entRot);
					nextRoom->SetActorRotation(FRotator(0.0f, angDif, 0.0f));

					FVector bOffset = nextRoom->GetActorLocation() - connection->billboard->GetComponentLocation();
					nextRoom->SetActorLocation(roomExits[i]->billboard->GetComponentLocation() + bOffset);

					TArray<AActor *> OverlappingActors;
					nextRoom->GetOverlappingActors(OverlappingActors);
					for (int8 b = 0; b < OverlappingActors.Num(); b++){
						ADungeonBase * isRoom = Cast<ADungeonBase>(OverlappingActors[b]);
						if (isRoom != NULL && isRoom != nextRoom){
							nextRoom->PrepareDestroy();
							nextRoom = NULL;
							attempts--;
							break;
						}
					}
					if (nextRoom != NULL){
						bSuccess = true;
						FVector loc = nextRoom->GetActorLocation();
						FRotator rot = nextRoom->GetActorRotation();
						nextRoom->PrepareDestroy();
						nextRoom = GetWorld()->SpawnActor<ADungeonBase>(DungeonCorridorClasses[ArrayIndex], loc, rot);
						nextRoom->GetComponents(nextRoomExits);
						connection = nextRoomExits[DoorIndex];

						AllDoors.Remove(roomExits[i]);
						roomExits[i]->DestroyComponent();
						connection->DestroyComponent();

						ToGenerateFromPlaceHolder.Remove(currentRoom);
						ToGenerateFromPlaceHolder.Add(nextRoom);
						AllRooms.Add(nextRoom);
					}
				}
				else{
					// If a room is to be generated
					int ArrayIndex = FMath::RandRange(0, DungeonRoomClasses.Num() - 1);
					nextRoom = GetWorld()->SpawnActor<ADungeonBase>(DungeonRoomClasses[ArrayIndex], FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));
					if (nextRoom == NULL){ break; }
					nextRoom->GetComponents(nextRoomExits);
					if (nextRoomExits.Num() == 0) { break; }
					int DoorIndex = FMath::RandRange(0, nextRoomExits.Num() - 1);
					UDungeonDoorway * connection; connection = nextRoomExits[DoorIndex];

					float entRot = connection->GetComponentRotation().Yaw;
					float exitRot = roomExits[i]->GetComponentRotation().Yaw;

					float angDif = (getOppositeAngle(exitRot) - entRot);
					nextRoom->SetActorRotation(FRotator(0.0f, angDif, 0.0f));

					FVector bOffset = nextRoom->GetActorLocation() - connection->billboard->GetComponentLocation();
					nextRoom->SetActorLocation(roomExits[i]->billboard->GetComponentLocation() + bOffset);

					TArray<AActor *> OverlappingActors;
					nextRoom->GetOverlappingActors(OverlappingActors);

					for (int8 b = 0; b < OverlappingActors.Num(); b++){
						ADungeonBase * isRoom = Cast<ADungeonBase>(OverlappingActors[b]);
						if (isRoom != NULL && isRoom != nextRoom){
							nextRoom->PrepareDestroy();
							nextRoom = NULL;
							attempts--;
							break;
						}
					}

					if (nextRoom != NULL){
						bSuccess = true;
						FVector loc = nextRoom->GetActorLocation();
						FRotator rot = nextRoom->GetActorRotation();
						nextRoom->PrepareDestroy();
						nextRoom = GetWorld()->SpawnActor<ADungeonBase>(DungeonRoomClasses[ArrayIndex], loc, rot);
						nextRoom->GetComponents(nextRoomExits);
						connection = nextRoomExits[DoorIndex];

						AllDoors.Remove(roomExits[i]);
						roomExits[i]->DestroyComponent();
						connection->DestroyComponent();

						ToGenerateFromPlaceHolder.Remove(currentRoom);
						ToGenerateFromPlaceHolder.Add(nextRoom);
						AllRooms.Add(nextRoom);
						NumOfRooms++;
					}
				}
			}
		}
	}
	bRoomCycle = !bRoomCycle;
	ToGenerateFrom = ToGenerateFromPlaceHolder;
	if (ToGenerateFrom.Num() == 0 && NumOfRooms < MinNumOfRooms){
		ResetDungeon();
	}
}
