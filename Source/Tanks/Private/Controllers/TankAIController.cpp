#include "Controllers/TankAIController.h"
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
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!CurrentTarget)
		FindClosestEnemyTank();

	FVector TargetLocation = CurrentTarget->GetActorLocation();
	float DistanceToTarget = FVector::Dist(ControlledTankPawn->GetActorLocation(), TargetLocation);

	if (DistanceToTarget < FireRange)
	{
		TakeAim();
		FireAtTarget();
	}
	else
	{
		MoveToTarget();
	}
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


	//UE_LOG(LogTemp, Display, TEXT("FOUND TARGET!"));

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

void ATankAIController::FindClosestEnemyTank()
{
	TArray <AActor *> FoundActors;
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
					CurrentTarget = TP;
					UE_LOG(LogTemp, Log, TEXT("Target Found!"));
				}
			}
		}
	}
}