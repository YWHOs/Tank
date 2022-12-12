// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TANK_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
	virtual void Tick(float _deltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	class APawnTank* tank;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float fireRange = 300.f;

	FTimerHandle fireRateTimer;
	float fireRate = 2.f;

	bool InFireRange();
	void CheckFire();
};
