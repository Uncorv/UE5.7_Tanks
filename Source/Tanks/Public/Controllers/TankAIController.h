#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATankPawn;
class ATankBase;

enum class TankAIState
{
	Idle,
	MoveToTarget,
	AttackTarget
};

UCLASS()
class TANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ATankAIController();

	void OnPossess(APawn *TankPawn) override;
	void Tick(float DelatTime) override;

private:
	void FindClosestTarget();
	ATankBase *FindEnemyBase() const;

	void MoveToTarget();
	void TakeAim();
	void FireAtTarget();

	bool IsAimAligned() const;
	bool IsTargetInFireRange() const;
	bool IsValidTarget() const;
	
	void UpdateState();
	void ExecuteState();

	UPROPERTY()
	ATankPawn *ControlledTankPawn;
	UPROPERTY()
	ATankBase *EnemyBase;
	UPROPERTY()
	AActor *CurrentTarget;

	float FireRange = 5000.f;
	TankAIState CurrentState = TankAIState::Idle;
};
