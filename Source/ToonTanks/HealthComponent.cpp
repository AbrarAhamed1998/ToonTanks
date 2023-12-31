// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksGameMode.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	
	CurrentGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UHealthComponent::DamageTaken(AActor* TargetActor, float DamageValue, const UDamageType* DamageType, class AController* Instigator, AActor* DamageApplier) 
{
	if (DamageValue <= 0) return;

	CurrentHealth -= DamageValue;

	//UE_LOG(LogTemp, Warning, TEXT("Health of Actor is %f."), CurrentHealth);

	if (CurrentHealth <= 0)
	{
		CurrentGameMode->ActorDied(TargetActor);
	}
}

