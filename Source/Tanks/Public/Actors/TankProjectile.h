#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TankProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class TANKS_API ATankProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ATankProjectile();

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit);

private:
	UPROPERTY(EditAnywhere)
	USphereComponent *SphereComponent;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent *ProjectileMesh;
	UPROPERTY(EditAnywhere)
	UProjectileMovementComponent *ProjectileMovementComponent;

	UPROPERTY(EditAnywhere)
	float Damage = 25.f;
	UPROPERTY(EditAnywhere)
	float LifeTime = 100.f;
	UPROPERTY(EditAnywhere)
	float ProjSpeed = 10000.f;

};
