// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	capsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
	RootComponent = capsuleComponent;

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));
	baseMesh -> SetupAttachment(capsuleComponent);

	turretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret"));
	turretMesh -> SetupAttachment(baseMesh);

	projectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn"));
	projectileSpawnPoint -> SetupAttachment(turretMesh);
}

void ABasePawn::RotateTurret(FVector _lookAtTarget)
{
	FVector toTarget = _lookAtTarget - turretMesh -> GetComponentLocation();
	FRotator lookAtRotation = FRotator(0.f, toTarget.Rotation().Yaw, 0.f);
	turretMesh -> SetWorldRotation(FMath::RInterpTo(turretMesh -> GetComponentRotation(),
	lookAtRotation, UGameplayStatics::GetWorldDeltaSeconds(this), 10.f));
}

