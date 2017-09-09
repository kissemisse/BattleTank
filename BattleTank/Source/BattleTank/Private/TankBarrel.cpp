// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float _relativeSpeed)
{
	_relativeSpeed = FMath::Clamp<float>(_relativeSpeed, -1.0f, 1.0f);

	float elevationChange = _relativeSpeed * maxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float rawNewElevation = RelativeRotation.Pitch + elevationChange;

	rawNewElevation = FMath::Clamp<float>(rawNewElevation, minElevationDegree, maxElevationDegree);

	SetRelativeRotation(FRotator(rawNewElevation, 0, 0));
}


