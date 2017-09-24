// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "TankBarrel.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent)) //make if accessible in blueprint
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max downard movement and +1 is max up movement
	void Elevate(float);

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float maxDegreesPerSecond = 5.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float maxElevationDegree = 30.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float minElevationDegree = 0.0f;

};
