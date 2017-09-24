// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAiController.h"
#include "TankAimingComponent.h"
#include "Tank.h" // need this to implemenet onDeath
#include "GameFramework/Pawn.h"

void ATankAiController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAiController::SetPawn(APawn *_inPawn)
{
	Super::SetPawn(_inPawn);

	if (_inPawn)
	{
		auto possesedTank = Cast<ATank>(_inPawn);

		if ( possesedTank )
		{
			// subrice our local method to the tanks death event
			possesedTank->OnDeath.AddUniqueDynamic(this, &ATankAiController::OnPossesedTankDeath);
		}
	}
}

void ATankAiController::OnPossesedTankDeath()
{
	APawn *pawn = GetPawn();
	
	if (!pawn) { return; }

	pawn->DetachFromControllerPendingDestroy();
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




