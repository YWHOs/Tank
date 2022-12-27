// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	projectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = projectileMesh;

	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	projectileMovement -> MaxSpeed = 1300.f;
	projectileMovement -> InitialSpeed = 1300.f;

	trailParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail"));
	trailParticle -> SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	projectileMesh -> OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	if(launchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, launchSound, GetActorLocation());
	}


}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* _hitComp, AActor* _otherActor, UPrimitiveComponent* _otherComp, FVector _normalImpulse, const FHitResult& _hit)
{
	AActor* myOwner = GetOwner();
	if(myOwner == nullptr)
	{
		Destroy();
		return;
	}

	AController* myOwnerInstigator = myOwner -> GetInstigatorController();
	UClass* damageTypeClass = UDamageType::StaticClass();

	if(_otherActor && _otherActor != this && _otherActor != myOwner)
	{
		UGameplayStatics::ApplyDamage(_otherActor, damage, myOwnerInstigator, this, damageTypeClass);
		if(hitParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, hitParticle, GetActorLocation(), GetActorRotation());
		}
		if(hitSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, hitSound, GetActorLocation());
		}
		if(hitCameraShakeClass)
		{
			GetWorld() -> GetFirstPlayerController() -> ClientStartCameraShake(hitCameraShakeClass);
		}
	}
	Destroy();
}

