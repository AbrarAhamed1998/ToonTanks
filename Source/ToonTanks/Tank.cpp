// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Spring Arm"));
	CameraSpringArm -> SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(CameraSpringArm);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);

	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

	//PlayerInputComponent->BindAxis(TEXT("RotateTurret"), this, &ATank::Look);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(GetController());

	
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerController)
	{
		FHitResult HitResult;
		bool isHit = PlayerController->GetHitResultUnderCursor(
			ECollisionChannel::ECC_Visibility,
			false,
			HitResult);
		if (isHit)
		{
			DrawDebugSphere(
				GetWorld(),
				HitResult.ImpactPoint,
				10,
				10,
				FColor::Red);
			RotateTurret(HitResult.ImpactPoint);
		}
	}
}



void ATank::Move(float AxisValue)
{
	FVector DeltaLocation(0.f);
	DeltaLocation.X = AxisValue * MovementSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(DeltaLocation, true, nullptr, ETeleportType::TeleportPhysics);
}

void ATank::Turn(float AxisValue)
{
	FRotator DeltaRot = FRotator::ZeroRotator;
	DeltaRot.Yaw = AxisValue * TankRotationSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(DeltaRot, true, nullptr, ETeleportType::TeleportPhysics);
}

