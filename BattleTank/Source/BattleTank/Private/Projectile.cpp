// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Engine/World.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	// make component visable/derived in blueprint

	collisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("CollisionsMesh")); // add component visible in BP
	SetRootComponent(collisionMesh); // set it as root 
	collisionMesh->SetNotifyRigidBodyCollision(true); // if the BP is copied this value will be copied as well as true (set as default)
	collisionMesh->SetVisibility(false); // another default value

	launchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("LaunchBlast"));
	launchBlast->AttachToComponent(collisionMesh, FAttachmentTransformRules::KeepRelativeTransform );

	projectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileComponent"));
	projectileMovementComponent->bAutoActivate = false; // we do not activate the component due to its beeing activated in a method when called from BP

	impactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("ImpactBlast"));
	impactBlast->AttachToComponent(collisionMesh, FAttachmentTransformRules::KeepRelativeTransform);
	impactBlast->bAutoActivate = false;

	explosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("ExplosionForce"));
	explosionForce->AttachToComponent(collisionMesh, FAttachmentTransformRules::KeepRelativeTransform);


}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	collisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit); // register an on hit event for the root object, calling onHit when the object hit something
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

void AProjectile::OnHit(UPrimitiveComponent *_hitComponent, AActor *_otherActor, UPrimitiveComponent *_otherComponent, FVector _normalImpulse, const FHitResult &_hit)
{
	launchBlast->Deactivate();
	impactBlast->Activate();
	explosionForce->FireImpulse(); // execute the impusel setup on the BP

	SetRootComponent(impactBlast); // set the impact blast as root and ..
	collisionMesh->DestroyComponent(); // destroy the mesh

	UGameplayStatics::ApplyRadialDamage(
		this,	// apply to this object
		projectileDamage,	//get the amount of damage
		GetActorLocation(),		// get this actor location and apply as Origin
		explosionForce->Radius,  // get the explosionorce radius and apply as radius
		UDamageType::StaticClass(), // no idea
		TArray<AActor*>());		// damage to all actors within the radius

	FTimerHandle	timer;
	GetWorld()->GetTimerManager().SetTimer(timer, this, &AProjectile::OnTimerExpire, destroyDelay, false); // add an event, call method onTimerExpire when destroyDelay has passeds (time)
		
}

void AProjectile::OnTimerExpire()
{
	Destroy(); // remote object (smoke and such) completely
}