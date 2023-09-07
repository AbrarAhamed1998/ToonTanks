// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
	
public:
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void HandleDestruction();

	APlayerController* GetPlayerTankController() const { return PlayerTankController; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Camera Attachements")
		class  USpringArmComponent* CameraSpringArm;
	UPROPERTY(VisibleAnywhere, Category = "Camera Attachements")
		class UCameraComponent* CameraComponent;
	UPROPERTY(EditDefaultsOnly, Category = "Tank Stats")
		float MovementSpeed = 2.f;
	UPROPERTY(EditDefaultsOnly, Category = "Tank Stats")
		float TankRotationSpeed = 2.f;

	APlayerController* PlayerTankController;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Move(float AxisValue);
	void Turn(float AxisValue);
};
