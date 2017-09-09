// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false; // no need, no tick component
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent *_hitComponent, AActor *_otherActor, UPrimitiveComponent *_otherComponent, FVector _normalImpulse, const FHitResult &_hit)
{
	DriveTrack();
	ApplySideWaysForce();
	currentThrottle = 0; //reset throttle
}

void UTankTrack::ApplySideWaysForce()
{
	// calculate the slippage speed
	float slippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity()); //track data, the right vector (not forward) and calc with the velocity
																						 // work-out the required acceleration this frame to correct
	float deltaTime = GetWorld()->GetDeltaSeconds();
	auto correctionAccelereration = -slippageSpeed / deltaTime * GetRightVector();
	// calculate and apply sideways for friction
	UStaticMeshComponent *tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());// fetch tank root
	auto correctionForce = (tankRoot->GetMass() * correctionAccelereration) / 2; // divided by 2 because two tracks
	tankRoot->AddForce(correctionForce);
}

void UTankTrack::SetThrottle(float _throttle)
{
	currentThrottle = FMath::Clamp<float>(currentThrottle + _throttle, -1, 1);
}

void UTankTrack::DriveTrack()
{
	FString	name = GetName();
	
	FVector	forceApplied = GetForwardVector() * currentThrottle * trackMaxDriveForce;
	FVector forceLocation = GetComponentLocation();
	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
}



