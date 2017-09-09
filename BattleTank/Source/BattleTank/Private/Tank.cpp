// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Getter for tankAimingComponent
// Couldnt get this to work after moving to forwarded classes and moving out the .h file
//UTankAimingComponent *ATank::GetTankAimingComponent() // Created this myself outside course, might come back later to this (we want to fetch the aimingcomponent since its declared in this class
//{
//	return tankAimingComponent;
//}

// Getter for launchSpeed
//float ATank::GetLaunchSpeed() {	return launchSpeed; }

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}


