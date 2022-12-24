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
    }
    else if (ATower* destroyedTower = Cast<ATower>(_deadActor))
    {
        destroyedTower -> HandleDestruction();
    }
}

void ATankGameMode::BeginPlay()
{
    Super::BeginPlay();

    GameStart();
}

void ATankGameMode::GameStart()
{
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