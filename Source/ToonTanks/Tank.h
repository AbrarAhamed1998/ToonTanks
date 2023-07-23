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
private:
	UPROPERTY(VisibleAnywhere, Category = "Camera Attachements")
		class  USpringArmComponent* CameraSpringArm;
	UPROPERTY(VisibleAnywhere, Category = "Camera Attachements")
		class UCameraComponent* CameraComponent;
	UPROPERTY(EditDefaultOnly, Category = "Tank Stats")
		float MovementSpeed = 2.f;
public:
	void Move(float AxisValue);
};
