// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	currentHealth = startingHealth;
}

float ATank::TakeDamage(float _damageAmount, struct FDamageEvent const &_damageEvent, AController *_eventInstigator, AActor *_damageCauser)
{
	int32 damagePoints = FPlatformMath::RoundToInt(_damageAmount); //convert incoming damage from float to int.
	int32 damageToApply = FMath::Clamp<int32>(damagePoints, 0, currentHealth); // ensure we are not loweing under 0

	currentHealth -= damageToApply; // decrease the damage from health

	if (currentHealth <= 0)
	{
		OnDeath.Broadcast();
	}

	return _damageAmount;
}

float ATank::GetHealthPercent() const
{
	return (float)currentHealth / (float)startingHealth;
}


