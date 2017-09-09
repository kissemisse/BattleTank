// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// make component visable/derived in blueprint

	collisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("CollisionsMesh")); // add component visible in BP
	SetRootComponent(collisionMesh); // set it as root 
	collisionMesh->SetNotifyRigidBodyCollision(true); // if the BP is copied this value will be copied as well as true (set as default)
	collisionMesh->SetVisibility(false); // another default value

	launchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("LaunchBlast"));
	launchBlast->AttachToComponent(collisionMesh, FAttachmentTransformRules::KeepWorldTransform);

	projectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileComponent"));
	projectileMovementComponent->bAutoActivate = false;


}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::LauncProjectile(float _speed)
{
	projectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * _speed);
	projectileMovementComponent->Activate();
}