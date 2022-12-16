// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankGameMode.h"
// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	health = maxHealth;
	
	GetOwner() -> OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::Damage);

	tankGameMode = Cast<ATankGameMode>(UGameplayStatics::GetGameMode(this));
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::Damage(AActor* _damageActor, float _damage, const UDamageType* _damageType, class AController* _instigator, AActor* _damageCauser)
{
	if (_damage <= 0.f) return;

	health -= _damage;
	if(health <= 0.f && tankGameMode)
	{
		tankGameMode -> ActorDied(_damageActor);
	}
}

