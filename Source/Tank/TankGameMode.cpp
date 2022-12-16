// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"
#include "Tower.h"
void ATankGameMode::ActorDied(AActor* _deadActor)
{
    if(_deadActor == tank)
    {
        tank -> HandleDestruction();
        if(tank -> GetTankPlayerController())
        {
            tank -> DisableInput(tank -> GetTankPlayerController());
            tank -> GetTankPlayerController() -> bShowMouseCursor = false;
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

    tank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}