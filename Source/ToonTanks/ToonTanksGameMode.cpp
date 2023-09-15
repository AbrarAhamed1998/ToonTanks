// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"


void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == PlayerTank)
	{
		PlayerTank->HandleDestruction();
		if (PlayerController)
		{
			PlayerController->SetPlayerEnabledState(false);
		}
		GameOver(false);
	}
	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
		TargetTowersCount--;
		if (TargetTowersCount <= 0)
		{
			GameOver(true);
		}
	}
}

void AToonTanksGameMode::HandleGameStart()
{
	PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	if (PlayerController)
	{
		StartGame();
		PlayerController->SetPlayerEnabledState(false);
		FTimerHandle PlayerStartTimerHandle;
		FTimerDelegate PlayerStartTimerDelegate = FTimerDelegate::CreateUObject(PlayerController, &AToonTanksPlayerController::SetPlayerEnabledState, true);

		GetWorldTimerManager().SetTimer(PlayerStartTimerHandle, PlayerStartTimerDelegate, StartDelay, false);
	}

	TargetTowersCount = GetAllTowersInWorld();
}

int32 AToonTanksGameMode::GetAllTowersInWorld()
{
	TArray<AActor*> TowersList;
	UGameplayStatics::GetAllActorsOfClass(
		this,
		ATower::StaticClass(),
		TowersList
	);
	return TowersList.Num();
}