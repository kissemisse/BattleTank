// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAiController.h"
#include "TankAimingComponent.h"

void ATankAiController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATankAiController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn	*playerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	if (!ensure(playerTank)) { return; }

	MoveToActor(playerTank, acceptenceRadius);
		
	UTankAimingComponent *aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(aimingComponent))
	{
		aimingComponent->AimAt(playerTank->GetActorLocation());

		if (aimingComponent->GetFiringState() == EFiringStatus::Locked)
		{
			aimingComponent->Fire();
		}
	}
}




