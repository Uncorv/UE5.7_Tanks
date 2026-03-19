#include "Controllers/TankPlayerController.h"
#include "Pawns/TankPawn.h"

void ATankPlayerController::OnPossess(APawn *NewPawn)
{
	Super::OnPossess(NewPawn);

	TankPawn = Cast<ATankPawn>(NewPawn);
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
	if (TankPawn)
	{
		TankPawn->MoveForward(Value);
	}
}

void ATankPlayerController::TurnRight(float Value)
{
	if (TankPawn)
	{
		TankPawn->TurnRight(Value);
	}
}

void ATankPlayerController::TurnTurretAndCamera(float Value)
{
	if (TankPawn)
	{
		TankPawn->TurnCameraAndTurret(Value);
	}
}
void ATankPlayerController::Fire()
{
	if (TankPawn)
	{
		TankPawn->Fire();
	}
}