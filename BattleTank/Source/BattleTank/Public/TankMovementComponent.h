// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * Driving tank tracks!
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BluePrintCallable, Category = "Input")
		void AddThrottleToTrack(UTankTrack *_track, float _throw);

	UFUNCTION(BluePrintCallable, Category = "Setup")
		void Initialize(UTankTrack *_leftTrack, UTankTrack *_rightTrack);

private:
	
	// Called from the pathFinding logic by the AI controllers
	virtual void RequestDirectMove(const FVector&, bool) override;

	UTankTrack	*leftTrack = nullptr;
	UTankTrack	*rightTrack = nullptr;



};
