#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATankPawn;

UCLASS()
class TANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void OnPossess(APawn *NewPawn) override;
	virtual void SetupInputComponent() override;

private:
	void MoveForward(float Value);
	void TurnRight(float Value);
	void TurnTurretAndCamera(float Value);
	void Fire();
};
