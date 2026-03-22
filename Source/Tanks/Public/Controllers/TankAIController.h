#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATankPawn;

enum class TankAIState
{
	Idle,
	MoveToEnemyTank,
	AttackEnemyTank,
	MoveToEnemyBase,
	AttackEnemyBase
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
	void FindClosestEnemyTank();
	void MoveToTarget();
	void TakeAim();
	void FireAtTarget();
	bool IsAimAligned() const;


	UPROPERTY()
	ATankPawn *ControlledTankPawn;
	UPROPERTY()
	AActor *CurrentTarget;

	float FireRange = 1200.f;

	TankAIState CurrentState = TankAIState::Idle;


};
