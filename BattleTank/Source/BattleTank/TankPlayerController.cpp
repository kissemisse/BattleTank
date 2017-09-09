// Fill out your copyright notice in the Description page of Project Settings.

// forwarded declared instead
#include "TankPlayerController.h"
#include "Public/TankAimingComponent.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	// in begin play the constructor have already run, so th component should be avaiable. fetch the component and use it in blue print.
	tankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(tankAimingComponent))
	{
		FoundAimingComponent(tankAimingComponent); // call blueprint event and send the aiming component
	}
}

void ATankPlayerController::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);

	AimTowardsCrosshair();
}

// Start the tank moving the barrel so that a shot would hit where crosshair intersects the world.
void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(tankAimingComponent)) { return; }

	FVector	hitLocation;

	if (GetSightRayHitLocation(hitLocation)) // modifies hitLocation if true (out parameter)
	{
		tankAimingComponent->AimAt(hitLocation );
	}
	
	return;
}

// Return an OUT parameter, true if hit landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& _outHitLocation ) const
{
	// Find the crosshair position in pixel coordinates
	int32	viewPortX, viewPortY;
	GetViewportSize(viewPortX, viewPortY);

	FVector2D screenLocation;
	screenLocation.X = viewPortX * crossHairXLocation;
	screenLocation.Y = viewPortY * crossHairYLocation;

	// "De-project" the screen position of the crosshair to a world direction
	FVector	lookDirection;
	if (GetLookDirection(screenLocation, lookDirection) )
	{
		// Get range using line trace by single channel getter
		return GetLookVectorHitLocation(lookDirection, _outHitLocation);
	}

	return false;
}

// De-project function
bool ATankPlayerController::GetLookDirection(FVector2D _screenLocation, FVector& _outLookDirection) const
{
	FVector	worldLocation; // Camera location, not needed

	return DeprojectScreenPositionToWorld(_screenLocation.X, _screenLocation.Y, worldLocation, _outLookDirection);
}

// Line trace get function
bool ATankPlayerController::GetLookVectorHitLocation( FVector _lookDirection, FVector &_hitLocation ) const
{
	FHitResult	hitResult;
	FVector	startLocation = PlayerCameraManager->GetCameraLocation();
	FVector endLocation = startLocation + (_lookDirection * lineTraceRange);

	//FCollisionQueryParams	params(FName(TEXT("")), false, GetOwner());

	if (GetWorld()->LineTraceSingleByChannel(
		hitResult,
		startLocation,
		endLocation,
		ECollisionChannel::ECC_Visibility ))
		//params))
	{
		_hitLocation = hitResult.Location;
		return true;
	}
	else
	{
		_hitLocation = FVector(0);
		return false;
	}
	
}


