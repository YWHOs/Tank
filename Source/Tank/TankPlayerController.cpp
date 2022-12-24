// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "GameFramework/Pawn.h"

void ATankPlayerController::SetPlayerEnabledState(bool _bPlayerEnabled)
{
    if(_bPlayerEnabled)
    {
        GetPawn() -> EnableInput(this);
    }
    else
    {
        GetPawn() -> DisableInput(this);
    }
    bShowMouseCursor = _bPlayerEnabled;
}
