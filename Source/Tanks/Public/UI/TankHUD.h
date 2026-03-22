#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TankHUD.generated.h"

UCLASS()
class TANKS_API ATankHUD : public AHUD
{
	GENERATED_BODY()

public:
	void BeginPlay() override;
	void DrawHUD() override;

private:
	UFont *Font;
};
