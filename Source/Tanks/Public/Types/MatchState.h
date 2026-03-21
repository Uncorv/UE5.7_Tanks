#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EMatchState : uint8
{
	WaitingToStart,
	InProgress,
	Finished
};