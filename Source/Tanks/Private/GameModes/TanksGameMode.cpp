#include "GameModes/TanksGameMode.h"
#include "GameModes/TanksGameState.h"

void ATanksGameMode::StartMatchFlow()
{
	if (CurrentMatchState == EMatchState::WaitingToStart)
	{
		CurrentMatchState = EMatchState::InProgress;
		UpdateGameState();
		UE_LOG(LogTemp, Log, TEXT("CurrentMatchState = MatchState::InProgress"));
	}
}

void ATanksGameMode::HandleTankDestroyed(ETeam Team)
{
	if (Team == ETeam::TeamA)
	{
		--AliveTanksTeamA;
	}
	else if (Team == ETeam::TeamB)
	{
		--AliveTanksTeamB;
	}
	UpdateGameState();
	CheckWinCondition();
}

void ATanksGameMode::HandleBaseDestroyed(ETeam Team)
{
	if (Team == ETeam::TeamA)
	{
		bIsBaseAliveTeamA = false;
	}
	else if (Team == ETeam::TeamB)
	{
		bIsBaseAliveTeamB = false;;
	}
	UpdateGameState();
	CheckWinCondition();
}

void ATanksGameMode::CheckWinCondition()
{
	if (AliveTanksTeamA <= 0 || !bIsBaseAliveTeamA)
	{
		EndMatch(ETeam::TeamB);
	}
	else if (AliveTanksTeamB <= 0 || !bIsBaseAliveTeamB)
	{
		EndMatch(ETeam::TeamA);
	}
}

void ATanksGameMode::EndMatch(ETeam Winner)
{
	UE_LOG(LogTemp, Log, TEXT("Winner team is: %d"), WinnerTeam);
	
	CurrentMatchState = EMatchState::Finished;
	WinnerTeam = Winner;
	UpdateGameState();
}

void ATanksGameMode::UpdateGameState()
{
	ATanksGameState *TanksGameState = GetGameState<ATanksGameState>();
	if (GameState)
	{
		TanksGameState->SetAliveTanksTeamA(AliveTanksTeamA);
		TanksGameState->SetAliveTanksTeamB(AliveTanksTeamB);
		TanksGameState->SetIsBaseAliveTeamA(bIsBaseAliveTeamA);
		TanksGameState->SetIsBaseAliveTeamB(bIsBaseAliveTeamB);
		TanksGameState->SetCurrentMatchState(CurrentMatchState);
		TanksGameState->SetWinnerTeam(WinnerTeam);
	}
}