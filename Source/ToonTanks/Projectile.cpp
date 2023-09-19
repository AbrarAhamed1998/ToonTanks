// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = BaseMesh;

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement Component"));
	MovementComponent->MaxSpeed = 1300.f;
	MovementComponent->InitialSpeed = 1300.f;

	TrailComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Trail"));
	TrailComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	BaseMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	if (LaunchSFX)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			LaunchSFX,
			GetActorLocation()
		);
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitInfo)
{
	/*UE_LOG(LogTemp, Warning, TEXT("Component Hit With : %s, Hit Actor : %s, Hit Component : %s"), 
		*HitComp->GetName(), *OtherActor->GetName(), *OtherComp->GetName());*/
	auto MyOwner = GetOwner();
	if (MyOwner == nullptr)
	{
		Destroy();
		return;
	}
	auto OwnerController = MyOwner->GetInstigatorController();
	
	auto DamageTypeClass = UDamageType::StaticClass();

	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(
			OtherActor,
			DamageValue,
			OwnerController,
			MyOwner,
			DamageTypeClass
		);
		if (HitSFX)
		{
			UGameplayStatics::PlaySoundAtLocation(
				this,
				HitSFX,
				GetActorLocation()
			);
		}
		if (HitCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
		}
	}

	if (HitParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this,
			HitParticles,
			GetActorLocation(),
			GetActorRotation());
	}

	
	
	Destroy();
}

