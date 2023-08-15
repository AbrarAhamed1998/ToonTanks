// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Find if tank in range 
	if (TargetTank)
	{
		float Distance = FVector::Distance(GetActorLocation(), TargetTank->GetActorLocation());

		if (Distance <= DetectionRange)
		{
			RotateTurret(TargetTank->GetActorLocation());
		}
	} 
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	TargetTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));
}
