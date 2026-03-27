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
	void BeginPlay() override;

	void StartMatchFlow();
	void HandleTankDestroyed(ETeam Team);
	void HandleBaseDestroyed(ETeam Team);
	void CheckWinCondition();
	void FindParticipants();
	void EndMatch(ETeam Winner);

	void UpdateGameState();

private:
	int AliveTanksTeamA = 0;
	int AliveTanksTeamB = 0;
	bool bIsBaseAliveTeamA = true;
	bool bIsBaseAliveTeamB = true;
	EMatchState CurrentMatchState = EMatchState::WaitingToStart; 
	ETeam WinnerTeam;
};
