// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Engine/World.h"
#include "TankAiController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAiController : public AAIController
{
	GENERATED_BODY()
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

protected:
	virtual void BeginPlay() override;

	// How close can the AI tank get near the player
	// need to be under protected so it can be accessed in the Blue Print class (its a child class to this c++ class) created from this class.
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float	acceptenceRadius = 8000.0f;


};
