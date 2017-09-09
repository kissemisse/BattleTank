// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "TankTurrent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent)) //make if accessible in blueprint
class BATTLETANK_API UTankTurrent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// -1 is max left movement and +1 is max right movement
	void Rotate(float);

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float maxDegreesPerSecond = 15.0f;

};
