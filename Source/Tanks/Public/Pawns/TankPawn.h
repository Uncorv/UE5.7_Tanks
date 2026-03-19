#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankPawn.generated.h"

class UBoxComponent;
class UCameraComponent;
class UHealthComponent;
class UInputComponent;
class USpringArmComponent;
class UTankMovementComponent;
class ATankProjectile;
class UWeaponComponent;

UCLASS()
class TANKS_API ATankPawn : public APawn
{
	GENERATED_BODY()

public:
	ATankPawn();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void MoveForward(float Value);
	void TurnRight(float Value);
	void TurnCameraAndTurret(float Value);
	void Fire();

	UFUNCTION()
	void OnTankDeath();

private:
	UPROPERTY(EditAnywhere)
	UBoxComponent *Box;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent *HullMesh;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent *TurretMesh;
	UPROPERTY(EditAnywhere)
	USceneComponent *MuzzlePoint;
	UPROPERTY(EditAnywhere)
	UTankMovementComponent *MovementComponent;
	UPROPERTY(EditAnywhere)
	UCameraComponent *CameraComponent;
	UPROPERTY(EditAnywhere)
	USpringArmComponent *SpringArmComponent;
	UPROPERTY(EditAnywhere)
	UHealthComponent *HealthComponent;
	UPROPERTY(EditAnywhere)
	UWeaponComponent *WeaponComponent;

	UPROPERTY(EditAnywhere)
	float TurretRotationSpeed = 300.f;
};
