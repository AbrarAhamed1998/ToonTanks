// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsTargetInRange())
		RotateTurret(TargetTank->GetActorLocation());
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	TargetTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));

	GetWorldTimerManager().SetTimer(FireTimeHandler, this,&ATower::CheckTimerHandler,FireRate, true);
}

void ATower::CheckTimerHandler()
{
	if (IsTargetInRange())
		Fire();
}

bool ATower::IsTargetInRange()
{
	if (TargetTank)
	{
		float Distance = FVector::Distance(GetActorLocation(), TargetTank->GetActorLocation());

		if (Distance <= DetectionRange)
		{
			return true;
		}
	}
	return false;
}