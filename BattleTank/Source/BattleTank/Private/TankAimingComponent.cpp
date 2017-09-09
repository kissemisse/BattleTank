// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurrent.h"
#include "Projectile.h"  // we need because we call the projectile class in this class in method Fire

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}
void UTankAimingComponent::BeginPlay()
{
	lastFireTime = GetWorld()->GetTimeSeconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ammo < 1)
	{
		firingStatus = EFiringStatus::OutOfAmmo;
	}
	else if ((GetWorld()->GetTimeSeconds() - lastFireTime) < reloadTimeInSeconds)
	{
		firingStatus = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving())
	{
		firingStatus = EFiringStatus::Aiming;
	}
	else
	{
		firingStatus = EFiringStatus::Locked;
	}
}

EFiringStatus UTankAimingComponent::GetFiringState() const
{
	return firingStatus;
}

void UTankAimingComponent::Initialize(UTankBarrel *_setBarrelReference, UTankTurrent *_setTurrentReference)
{
	barrel = _setBarrelReference;
	turrent = _setTurrentReference;
}

int UTankAimingComponent::GetAmmo() const { return ammo; }

bool UTankAimingComponent::IsBarrelMoving()
{
	bool ret = false;

	if (ensure(barrel))
	{
		FVector	currentForwardVector = barrel->GetForwardVector();
		ret = !currentForwardVector.Equals(aimDirection, 0.01f); // checks if equals, if so return false (its not moving) else true (it is moving)
	}

	return ret;
}

void UTankAimingComponent::Fire()
{
	if( firingStatus == EFiringStatus::Locked || firingStatus == EFiringStatus::Aiming )
	{
		if (!ensure(projectileBluePrint)) { return; } // splitting into two gives us more information if error
		if (!ensure(barrel)) { return; }

		AProjectile *projectile = GetWorld()->SpawnActor<AProjectile>(projectileBluePrint, barrel->GetSocketLocation(FName("Projectile")), barrel->GetSocketRotation(FName("Projectile")));

		projectile->LauncProjectile(launchSpeed);

		lastFireTime = GetWorld()->GetTimeSeconds();
		ammo--;

	}
}

void UTankAimingComponent::AimAt(FVector _hitLocation)
{
	if (!ensure(barrel)) { return; } // ensure we have it or else crash
		
	FVector		outLaunchVelocity;
	FVector		startLocation =  barrel->GetSocketLocation(FName("Projectile"));

	bool haveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this,
		outLaunchVelocity,	// store fvector
		startLocation,
		_hitLocation,
		launchSpeed,
		false,
		0.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace); // Must be present to prevent possible bug
	
	if(haveAimSolution)
	{
		aimDirection = outLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(aimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector _aimDirection)
{
	if (!ensure(turrent) || !ensure(barrel)) { return; }
	
	FRotator barrelRotation = barrel->GetForwardVector().Rotation();
	FRotator aimAsRotator = _aimDirection.Rotation();
	FRotator deltaRotator = aimAsRotator - barrelRotation;
	
	barrel->Elevate(deltaRotator.Pitch);
	
	if (FMath::Abs(deltaRotator.Yaw) < 180)
	{
		turrent->Rotate(deltaRotator.Yaw);
	}
	else
	{
		turrent->Rotate(-deltaRotator.Yaw);
	}
}



