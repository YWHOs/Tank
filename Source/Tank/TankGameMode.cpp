// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"
#include "Tower.h"
#include "TankPlayerController.h"

void ATankGameMode::ActorDied(AActor* _deadActor)
{
    if(_deadActor == tank)
    {
        tank -> HandleDestruction();
        if(tankPlayerController)
        {
            tankPlayerController -> SetPlayerEnabledState(false);
        }
        GameOver(false);
    }
    else if (ATower* destroyedTower = Cast<ATower>(_deadActor))
    {
        destroyedTower -> HandleDestruction();
        --targetTowers;
        if(targetTowers == 0)
        {
            GameOver(true);
        }
    }
}

void ATankGameMode::BeginPlay()
{
    Super::BeginPlay();

    GameStart();
}

void ATankGameMode::GameStart()
{
    targetTowers = GetTargetTower();
    tank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
    tankPlayerController = Cast<ATankPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    StartGame();
    if(tankPlayerController)
    {
        tankPlayerController -> SetPlayerEnabledState(false);

        FTimerHandle playerEnableTime;

        FTimerDelegate inputDelegate = FTimerDelegate::CreateUObject(tankPlayerController,
        &ATankPlayerController::SetPlayerEnabledState, true);

        GetWorldTimerManager().SetTimer(playerEnableTime, inputDelegate, startDelay, false);
    }
}

int32 ATankGameMode::GetTargetTower()
{
    TArray<AActor*> towers;
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), towers);
    return towers.Num();
}