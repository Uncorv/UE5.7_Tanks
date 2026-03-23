#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Types/Team.h"
#include "Types/MatchState.h"
#include "TanksGameMode.generated.h"

class ATanksGameState;

UCLASS()
class TANKS_API ATanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void StartMatchFlow();
	void HandleTankDestroyed(ETeam Team);
	void HandleBaseDestroyed(ETeam Team);
	void CheckWinCondition();
	void EndMatch(ETeam Winner);

	void UpdateGameState();

private:
	int AliveTanksTeamA = 2;
	int AliveTanksTeamB = 2;
	bool bIsBaseAliveTeamA = true;
	bool bIsBaseAliveTeamB = true;
	EMatchState CurrentMatchState = EMatchState::WaitingToStart; 
	ETeam WinnerTeam;
};
