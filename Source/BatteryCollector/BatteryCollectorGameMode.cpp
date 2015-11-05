// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "BatteryCollector.h"
#include "BatteryCollectorGameMode.h"
#include "BatteryCollectorCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "SpawnVolume.h"

ABatteryCollectorGameMode::ABatteryCollectorGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// Set base decay rate
	DecayRate = 0.01f;
}

void ABatteryCollectorGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Find all spawn volumes Actors
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundActors);

	for (auto Actor : FoundActors)
	{
		ASpawnVolume* SpawnVolumeActor = Cast<ASpawnVolume>(Actor);
		if (SpawnVolumeActor)
		{
			SpawnVolumeActors.AddUnique(SpawnVolumeActor);
		}
	}

	SetCurrentSate(EBatteryPlayState::EPlaying);

	// Set the score to beat
	ABatteryCollectorCharacter* MyCharacter = Cast<ABatteryCollectorCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (MyCharacter)
	{
		PowerToWin = (MyCharacter->GetInitialPower()) * 1.25f;
	}

	if (HUDWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

void ABatteryCollectorGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Check that we are using the battery collector character
	ABatteryCollectorCharacter* MyCharacter = Cast<ABatteryCollectorCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (MyCharacter) 
	{
		// If our power is greqter than the power needed to win
		if (MyCharacter->GetCurrentPower() > PowerToWin){
			// Set the game state to won
			SetCurrentSate(EBatteryPlayState::EWon);
		}
		// if the character'q power is positive
		else if (MyCharacter->GetCurrentPower() > 0)
		{
			// Character's power level decays
			MyCharacter->UpdatePower(-DeltaTime*DecayRate*MyCharacter->GetInitialPower());
		}
		else
		{
			// Set the game state to game over
			SetCurrentSate(EBatteryPlayState::EGameOver);
		}
	}
}

float ABatteryCollectorGameMode::GetPowerToWin() const
{
	return PowerToWin;
}

EBatteryPlayState ABatteryCollectorGameMode::GetCurrentState() const
{
	return CurrentState;
}


void ABatteryCollectorGameMode::SetCurrentSate(EBatteryPlayState NewState)
{
	// Set the current state
	CurrentState = NewState;
	// Handle the new state
	HandleNewState(NewState);
}

void ABatteryCollectorGameMode::HandleNewState(EBatteryPlayState NewState)
{
	switch (NewState)
	{
	// If the game is playing
	case EBatteryPlayState::EPlaying:
	{
		// Spawn volumes actives
		for (ASpawnVolume* Volume : SpawnVolumeActors)
		{
			Volume->SetSpawningActive(true);
		}
	}
	break;
	// If the game is won
	case EBatteryPlayState::EWon:
	{
		// Spawn volumes inactives
		for (ASpawnVolume* Volume : SpawnVolumeActors)
		{
			Volume->SetSpawningActive(false);
		}
	}
	break;
	// If the game is lost
	case EBatteryPlayState::EGameOver:
	{
		// Spawn volumes inactives
		for (ASpawnVolume* Volume : SpawnVolumeActors)
		{
			Volume->SetSpawningActive(false);
		}
		// Block player input
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (PlayerController){
			PlayerController->SetCinematicMode(true, false, false, true, true);
		}
		// Kill character
		ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
		if (MyCharacter)
		{
			MyCharacter->GetMesh()->SetSimulatePhysics(true);
			MyCharacter->GetMovementComponent()->MovementState.bCanJump = false;
		}
	}
	break;
	// Unkown state
	case EBatteryPlayState::EUnknown:
	{

	}
	break;
	}
}
