// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"

APawnTank::APawnTank()
{
    springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring"));
    springArm -> SetupAttachment(RootComponent);

    camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    camera -> SetupAttachment(springArm);
}
void APawnTank::SetupPlayerInputComponent(UInputComponent* _playerInputComponent)
{
    Super::SetupPlayerInputComponent(_playerInputComponent);

    _playerInputComponent -> BindAxis(TEXT("Moveforward"), this, &APawnTank::Move);
    _playerInputComponent -> BindAxis(TEXT("Turn"), this, &APawnTank::Turn);
}

void APawnTank::Move(float _value)
{
    FVector deltaLocation = FVector::ZeroVector;
    deltaLocation.X = _value * speed * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalOffset(deltaLocation, true);
}

void APawnTank::Turn(float _value)
{
    FRotator deltaRotation = FRotator::ZeroRotator;
    deltaRotation.Yaw = _value * turnSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalRotation(deltaRotation, true);
}