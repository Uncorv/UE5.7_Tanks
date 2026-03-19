#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ETeam : uint8
{
	None UMETA(DisplayName = "None"),
	TeamA UMETA(DisplayName = "TeamA"),
	TeamB UMETA(DisplayName = "TeamB")
};

