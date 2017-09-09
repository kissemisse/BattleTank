// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack *_leftTrack, UTankTrack *_rightTrack)
{
	leftTrack = _leftTrack;
	rightTrack = _rightTrack;
}

void UTankMovementComponent::AddThrottleToTrack(UTankTrack *_track, float _throw)
{
	if (!ensure(_track)) { return; }

	_track->SetThrottle(_throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector &_moveVelocity, bool _bForceMaxSpeed)
{
	FVector tankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector aiForwardIntention = _moveVelocity.GetSafeNormal();

	float forwardThrow = FVector::DotProduct(tankForward, aiForwardIntention);
	AddThrottleToTrack(leftTrack, forwardThrow);
	AddThrottleToTrack(rightTrack, forwardThrow);

	float rightThrow = FVector::CrossProduct(tankForward, aiForwardIntention).Z;
	AddThrottleToTrack(leftTrack, rightThrow);

	//UE_LOG(LogTemp, Warning, TEXT("calc right: %f forward: %f"), rightThrow, forwardThrow);


}


