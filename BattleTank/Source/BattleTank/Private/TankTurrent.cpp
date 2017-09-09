// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurrent.h"

void UTankTurrent::Rotate(float _relativeSpeed)
{
	_relativeSpeed = FMath::Clamp<float>(_relativeSpeed, -1.0f, 1.0f);

	float rotateChange = _relativeSpeed * maxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float newRotation = RelativeRotation.Yaw + rotateChange;

	SetRelativeRotation(FRotator(0, newRotation, 0));

}


