// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "PawnTank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float _deltaTime)
{
    Super::Tick(_deltaTime);

    if (InFireRange())
    {
        RotateTurret(tank -> GetActorLocation());
    }

}

void ATower::BeginPlay()
{
    Super::BeginPlay();

    tank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(fireRateTimer, this, &ATower::CheckFire, fireRate, true);
}

void ATower::CheckFire()
{
    if (InFireRange())
    {
        Fire();
    }
}

bool ATower::InFireRange()
{
    if (tank)
    {
        float distance = FVector::Dist(GetActorLocation(), tank -> GetActorLocation());
        if(distance <= fireRange)
            return true;
    }
    return false;
}