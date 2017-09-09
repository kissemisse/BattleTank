// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/GameplayStatics.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo

};

// Forward declarations
class UTankBarrel; 
class UTankTurrent;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFUNCTION(BluePrintCallable, Category = "Setup")
		void Initialize(UTankBarrel *_setBarrelReference, UTankTurrent *_setTurrentReference);

	UFUNCTION(BlueprintCallable) // this makes this method visable in the blue print
		void Fire();

	UFUNCTION(BlueprintCallable) // this makes this method visable in the blue print
		int32 GetAmmo() const;

	UTankAimingComponent();

	void AimAt(FVector);

	EFiringStatus GetFiringState() const;


protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringStatus	firingStatus = EFiringStatus::Reloading;

private:
	virtual void BeginPlay() override;
	virtual void TickComponent(float, enum ELevelTick, FActorComponentTickFunction*) override;

	void MoveBarrelTowards(FVector);
	bool IsBarrelMoving();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")			// Adds option on tank blue print to add the class type defined (Projectile_BP)
		TSubclassOf<AProjectile>	projectileBluePrint;	

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float launchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float reloadTimeInSeconds = 3.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		int32 ammo = 3; // use int32 instead of int

	UTankBarrel		*barrel = nullptr;
	UTankTurrent	*turrent = nullptr;

	// Stores the direction we are aiming at, needed in multiple methods
	FVector	aimDirection;

	double lastFireTime = 0;


};
