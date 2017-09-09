// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * This text will show up in the properties text (when hoovering the mouse over) this component in Blueprint.
*/
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent)) //make if accessible in blueprint
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:
	UFUNCTION(BluePrintCallable, Category = Input)
		void SetThrottle(float _throttle);
	
	// Max force per track in Nm
	UPROPERTY(EditDefaultsOnly)
		float trackMaxDriveForce = 400000.0f; // assume 40ton tank and 1g acceleration

private:
	UTankTrack();
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnHit(UPrimitiveComponent *_hitComponent, AActor *_otherActor, UPrimitiveComponent *_otherComponent, FVector _normalImpulse, const FHitResult &_hit);

	void ApplySideWaysForce();
	void DriveTrack();

	float currentThrottle = 0.0f;

};
