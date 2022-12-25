// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TANK_API ATankGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(AActor* _deadActor);

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool _wonGame);

protected:
	virtual void BeginPlay() override;

private:
	class APawnTank* tank;
	class ATankPlayerController* tankPlayerController;

	float startDelay = 3.f;

	void GameStart();

	int32 targetTowers = 0;
	int32 GetTargetTower();
	
};
