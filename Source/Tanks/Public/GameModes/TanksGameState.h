#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Types/MatchState.h"
#include "Types/Team.h"
#include "TanksGameState.generated.h"

UCLASS()
class TANKS_API ATanksGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	int GetAliveTanksTeamA() const;
	int GetAliveTanksTeamB() const;
	bool IsBaseAliveTeamA() const;
	bool IsBaseAliveTeamB() const;
	EMatchState GetCurrentMatchState() const;
	ETeam GetWinnerTeam() const;

	void SetAliveTanksTeamA(int AliveTanks);
	void SetAliveTanksTeamB(int AliveTanks);
	void SetIsBaseAliveTeamA(bool bIsAlive);
	void SetIsBaseAliveTeamB(bool bIsAlive);
	void SetCurrentMatchState(EMatchState MatchState);
	void SetWinnerTeam(ETeam Winner);

private:
	int AliveTanksTeamA = 0;
	int AliveTanksTeamB = 0;
	bool bIsBaseAliveTeamA = true;
	bool bIsBaseAliveTeamB = true;
	EMatchState CurrentMatchState = EMatchState::WaitingToStart;
	ETeam WinnerTeam = ETeam::None;

};
