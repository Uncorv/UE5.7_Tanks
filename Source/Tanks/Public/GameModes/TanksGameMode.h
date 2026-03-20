#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Types/Team.h"
#include "TanksGameMode.generated.h"

enum class MatchState
{
	WaitingToStart,
	InProgress,
	Finished
};

UCLASS()
class TANKS_API ATanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	void StartMatchFlow();
	void HandleTankDestroyed(ETeam Team);
	void HandleBaseDestroyed(ETeam Team);
	void CheckWinCondition();
	void EndMatch(ETeam WinnerTeam);

private:
	int AliveTanksTeamA = 1;
	int AliveTanksTeamB = 1;
	bool bIsBaseAliveTeamA = true;
	bool bIsBaseAliveTeamB = true;
	MatchState CurrentMatchState = MatchState::WaitingToStart; 
};
