#include "Controllers/TankPlayerController.h"
#include "Pawns/TankPawn.h"

void ATankPlayerController::OnPossess(APawn *NewPawn)
{
	Super::OnPossess(NewPawn);
}

void ATankPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	check(InputComponent);
	InputComponent->BindAxis("MoveForward", this, &ATankPlayerController::MoveForward);
	InputComponent->BindAxis("TurnRight", this, &ATankPlayerController::TurnRight);
	InputComponent->BindAxis("TurnTurret", this, &ATankPlayerController::TurnTurretAndCamera);

	InputComponent->BindAction("Fire", IE_Pressed, this, &ATankPlayerController::Fire);
}

void ATankPlayerController::MoveForward(float Value)
{
	ATankPawn *TP = Cast<ATankPawn>(GetPawn());
	if (IsValid(TP))
	{
		TP->MoveForward(Value);
	}
}

void ATankPlayerController::TurnRight(float Value)
{	
	ATankPawn *TP = Cast<ATankPawn>(GetPawn());
	if (IsValid(TP))
	{
		TP->TurnRight(Value);
	}
}

void ATankPlayerController::TurnTurretAndCamera(float Value)
{
	ATankPawn *TP = Cast<ATankPawn>(GetPawn());
	if (IsValid(TP))
	{
		TP->TurnCameraAndTurret(Value);
	}
}
void ATankPlayerController::Fire()
{
	ATankPawn *TP = Cast<ATankPawn>(GetPawn());
	if (IsValid(TP))
	{
		TP->Fire();
	}
}