#include "GameModes/TanksGameMode.h"

void ATanksGameMode::StartMatchFlow()
{
	if (CurrentMatchState == MatchState::WaitingToStart)
	{
		CurrentMatchState = MatchState::InProgress;
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

void ATanksGameMode::EndMatch(ETeam WinnerTeam)
{
	UE_LOG(LogTemp, Log, TEXT("Winner team is: %d"), WinnerTeam);
	CurrentMatchState = MatchState::Finished;
}