// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent; //forward declerations, use in .h but include in cpp (unless unreal objects)
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float) override;

protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup") //can be protected since the blueprint is derrived from this class. Also does not need to be in cpp file!
		void FoundAimingComponent(UTankAimingComponent *aimingComponentReference);

private:

	void AimTowardsCrosshair();
	bool GetLookVectorHitLocation(FVector, FVector&) const;

	bool GetSightRayHitLocation(FVector&) const; 

	bool GetLookDirection(FVector2D, FVector&) const;

	UPROPERTY(EditAnywhere)
		float lineTraceRange = 1000000.0f; // 10km

	UPROPERTY(EditAnywhere)
		float crossHairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
		float crossHairYLocation = 0.3f;

	UTankAimingComponent	*tankAimingComponent;

protected:
	virtual void BeginPlay() override;


};
