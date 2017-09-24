// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Controller.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	
	ATank();

	// Returns current health as a percentage of starting health, between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Health")
		float GetHealthPercent() const;

	// Called by the engine when actor damage is dealt
	virtual float TakeDamage(float _damageAmount, struct FDamageEvent const &_damageEvent, AController *_eventInstigator, AActor *_damageCauser) override;

	FTankDelegate OnDeath;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Sets default values for this pawn's properties
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		int32	startingHealth = 100;
	
	UPROPERTY(VisibleAnywhere, Category = "Health")
		int32	currentHealth; // initlized in begin play, do not use startingHealth because that can be set in blueprint

};
