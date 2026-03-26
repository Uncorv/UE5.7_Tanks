#include "Controllers/TankAIController.h"
#include "Actors/TankBase.h"
#include "Kismet/GameplayStatics.h"
#include "Pawns/TankPawn.h"

ATankAIController::ATankAIController()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ATankAIController::OnPossess(APawn *TankPawn)
{
	Super::OnPossess(TankPawn);

	ControlledTankPawn = Cast<ATankPawn>(TankPawn);
	EnemyBase = FindEnemyBase();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateState();
	ExecuteState();
}

void ATankAIController::MoveToTarget()
{
	FVector TankLocation = ControlledTankPawn->GetActorLocation();
	FVector TargetLocation = CurrentTarget->GetActorLocation();
	FVector TargetDirection = (TargetLocation - TankLocation).GetSafeNormal();
	FVector ForwardVector = ControlledTankPawn->GetActorForwardVector();

	float ForwardDot = FVector::DotProduct(ForwardVector, TargetDirection);
	float ThrottleValue = FMath::Clamp(ForwardDot, -1.f, 1.f);

	float TargetYaw = TargetDirection.Rotation().Yaw;
	float CurrentYaw = ForwardVector.Rotation().Yaw;
	float DeltaYaw = FMath::FindDeltaAngleDegrees(CurrentYaw, TargetYaw);
	float TurnValue = FMath::Clamp(DeltaYaw / 45.f, -1.f, 1.f); // 45 — sensitivity of the turning

	ControlledTankPawn->MoveForward(ThrottleValue);
	ControlledTankPawn->TurnRight(TurnValue);
}

void ATankAIController::TakeAim()
{
	FVector TurretLocation = ControlledTankPawn->GetCurrentTurretLocation();
	FVector TargetLocation = CurrentTarget->GetActorLocation();
	FVector DirectionToTarget = (TargetLocation - TurretLocation).GetSafeNormal();
	float CurrentTurretYaw = ControlledTankPawn->GetCurrentTurretRotation().Yaw;
	float TargetYaw = DirectionToTarget.Rotation().Yaw;
	float DeltaYaw = FMath::FindDeltaAngleDegrees(CurrentTurretYaw, TargetYaw);
	float TurnValue = FMath::Clamp(DeltaYaw / 45.f, -1.f, 1.f); // 45 — sensitivity of the turning

	ControlledTankPawn->TurnCameraAndTurret(TurnValue);
}

void ATankAIController::FireAtTarget()
{
	if (ControlledTankPawn->CanFire() && IsAimAligned())
	{
		UE_LOG(LogTemp, Display, TEXT("FIRING!"));
		ControlledTankPawn->Fire();
	}
}

bool ATankAIController::IsAimAligned() const
{
	FVector TurretLocation = ControlledTankPawn->GetCurrentTurretLocation();
	FVector TargetLocation = CurrentTarget->GetActorLocation();
	float CurrentTurretYaw = ControlledTankPawn->GetCurrentTurretRotation().Yaw;
	FVector DirectionToTarget = (TargetLocation - TurretLocation).GetSafeNormal();
	float TargetYaw = DirectionToTarget.Rotation().Yaw;
	float DeltaYaw = FMath::FindDeltaAngleDegrees(CurrentTurretYaw, TargetYaw);

	return FMath::Abs(DeltaYaw) <= 15.f;
}

void ATankAIController::FindClosestTarget()
{
	TArray <AActor *> FoundActors;
	TArray<ATankPawn *>EnemyTanks;
	UGameplayStatics::GetAllActorsOfClass(this, ATankPawn::StaticClass(), FoundActors);

	if (!FoundActors.IsEmpty())
	{
		for (AActor *Actor : FoundActors)
		{
			ATankPawn *TP = Cast<ATankPawn>(Actor);
			if (TP)
			{
				if (TP != ControlledTankPawn && TP->GetTeam() != ControlledTankPawn->GetTeam() && !TP->IsDead())
				{
					EnemyTanks.Add(TP);
				}
			}
		}
	}

	if (!EnemyTanks.IsEmpty())
	{
		ATankPawn *Closest = nullptr;
		float MinDist = FLT_MAX;
		for (ATankPawn *Tank : EnemyTanks)
		{
			float Dist = FVector::Dist(ControlledTankPawn->GetActorLocation(), Tank->GetActorLocation());
			if (Dist < MinDist)
			{
				MinDist = Dist;
				Closest = Tank;
			}
		}
		CurrentTarget = Closest;
	}
	else
	{
		CurrentTarget = EnemyBase;
	}
}

ATankBase *ATankAIController::FindEnemyBase() const
{
	TArray <AActor *> Bases;
	UGameplayStatics::GetAllActorsOfClass(this, ATankBase::StaticClass(), Bases);

	if (!Bases.IsEmpty())
	{
		for (AActor *Base : Bases)
		{
			ATankBase *TB = Cast<ATankBase>(Base);
			if (TB)
			{
				if (!TB->IsDead() && TB->GetTeam() != ControlledTankPawn->GetTeam())
				{
					return TB;
				}
			}
		}
	}
	return nullptr;
}

bool ATankAIController::IsTargetInFireRange() const
{
	FVector TargetLocation = CurrentTarget->GetActorLocation();
	float DistanceToTarget = FVector::Dist(ControlledTankPawn->GetActorLocation(), TargetLocation);

	return DistanceToTarget < FireRange;
}

bool ATankAIController::IsValidTarget() const
{
	ATankPawn *TP = Cast<ATankPawn>(CurrentTarget);
	ATankBase *TB = Cast<ATankBase>(CurrentTarget);
	if (TP)
	{
		return (TP && !TP->IsDead() && TP->GetTeam() != ControlledTankPawn->GetTeam());
	}
	else if (TB)
	{
		return (!TB->IsDead() && TB->GetTeam() != ControlledTankPawn->GetTeam());
	}
	else
	{
		return false;
	}
}

void ATankAIController::UpdateState()
{
	if (IsValidTarget())
	{
		if (IsTargetInFireRange())
		{
			CurrentState = TankAIState::AttackTarget;
		}
		else
		{
			CurrentState = TankAIState::MoveToTarget;
		}
	}
	else
	{
		CurrentState = TankAIState::Idle;
	}
}

void ATankAIController::ExecuteState()
{
	if (CurrentState == TankAIState::Idle)
	{
		FindClosestTarget();
	}
	else if (CurrentState == TankAIState::MoveToTarget)
	{
		TakeAim();
		MoveToTarget();
	}
	else if (CurrentState == TankAIState::AttackTarget)
	{
		TakeAim();
		FireAtTarget();
	}
}