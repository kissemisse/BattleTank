// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();
	
	virtual void Tick(float DeltaTime) override;
	
	void LauncProjectile(float);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:

	UFUNCTION()
		void OnHit(UPrimitiveComponent *_hitComponent, AActor *_otherActor, UPrimitiveComponent *_otherComponent, FVector _normalImpulse, const FHitResult &_hit);
	
	void OnTimerExpire();
	
	UProjectileMovementComponent	*projectileMovementComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent	*collisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UParticleSystemComponent	*launchBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UParticleSystemComponent	*impactBlast = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
		URadialForceComponent	*explosionForce = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Setup" )
		float destroyDelay = 10.f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float projectileDamage = 20.0f;
};
