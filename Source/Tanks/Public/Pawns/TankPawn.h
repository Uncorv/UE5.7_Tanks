#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Types/Team.h"
#include "TankPawn.generated.h"

class UBoxComponent;
class UCameraComponent;
class UHealthComponent;
class UInputComponent;
class UNiagaraSystem;
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

	void PlayVFXFire();
	void PlayVFXHit();
	void PlayVFXDeath();

	bool CanFire() const;
	ETeam GetTeam() const;
	float GetCurrentHealth() const;
	bool IsDead() const;
	FRotator GetCurrentTurretRotation() const;
	FVector GetCurrentTurretLocation() const;

	UFUNCTION()
	void OnTankDeath();
	UFUNCTION()
	void OnTankHealthChanged();

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
	UPROPERTY(EditAnywhere, Category = "VFX")
	UNiagaraSystem *NiagaraFire;
	UPROPERTY(EditAnywhere, Category = "VFX")
	UNiagaraSystem *NiagaraHit;
	UPROPERTY(EditAnywhere, Category = "VFX")
	UNiagaraSystem *NiagaraDeath;
	UPROPERTY(EditAnywhere)
	ETeam Team = ETeam::None;

	UPROPERTY(EditAnywhere)
	float TurretRotationSpeed = 300.f;
};
