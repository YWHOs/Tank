// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "PawnTank.generated.h"

/**
 * 
 */
UCLASS()
class TANK_API APawnTank : public ABasePawn
{
	GENERATED_BODY()

public:
	APawnTank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* springArm;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* camera;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	float speed = 200.0f;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float turnSpeed = 45.f;
	void Move(float _value);
	void Turn(float _value);
};
