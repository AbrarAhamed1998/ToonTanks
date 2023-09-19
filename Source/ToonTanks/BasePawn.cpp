// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Projectile.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasePawn::HandleDestruction()
{
	//TODO: VFX and SFX
	if (DeathParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			this,
			DeathParticles,
			GetActorLocation(),
			GetActorRotation()
		);
	}

	if (DeathSFX)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			DeathSFX,
			GetActorLocation()
		);
	}

	if (DeathCameraShake)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShake);
	}
}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABasePawn::RotateTurret(FVector LookAtPos)
{
	FRotator LookAtRotation = (LookAtPos - TurretMesh->GetComponentLocation()).Rotation();
	
	LookAtRotation = FRotator(0.0f, LookAtRotation.Yaw, 0.0f);

	TurretMesh->SetWorldRotation(FMath::RInterpTo(
		TurretMesh->GetComponentRotation(), 
		LookAtRotation, UGameplayStatics::GetWorldDeltaSeconds(this),
		TurretRotationSpeed));
}

void ABasePawn::Fire()
{
	FVector debugSphereLoc = ProjectileSpawnPoint->GetComponentLocation();

	/*DrawDebugSphere(
		GetWorld(),
		debugSphereLoc,
		10,
		10,
		FColor::Red,
		false,
		3.0f);*/

	AProjectile* FiredProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, debugSphereLoc, ProjectileSpawnPoint->GetComponentRotation());
	FiredProjectile->SetOwner(this);
}

