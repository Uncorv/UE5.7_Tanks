#include "GameModes/TanksGameState.h"

int ATanksGameState::GetAliveTanksTeamA() const
{
	return AliveTanksTeamA;
}

int ATanksGameState::GetAliveTanksTeamB() const
{
	return AliveTanksTeamB;
}

bool ATanksGameState::IsBaseAliveTeamA() const
{
	return bIsBaseAliveTeamA;
}

bool ATanksGameState::IsBaseAliveTeamB() const
{
	return bIsBaseAliveTeamB;
}

EMatchState ATanksGameState::GetCurrentMatchState() const
{
	return CurrentMatchState;
}

ETeam ATanksGameState::GetWinnerTeam() const
{
	return WinnerTeam;
}

void ATanksGameState::SetAliveTanksTeamA(int AliveTanks)
{
	AliveTanksTeamA = AliveTanks;
}

void ATanksGameState::SetAliveTanksTeamB(int AliveTanks)
{
	AliveTanksTeamB = AliveTanks;
}

void ATanksGameState::SetIsBaseAliveTeamA(bool bIsAlive)
{
	bIsBaseAliveTeamA = bIsAlive;
}

void ATanksGameState::SetIsBaseAliveTeamB(bool bIsAlive)
{
	bIsBaseAliveTeamB = bIsAlive;
}

void ATanksGameState::SetCurrentMatchState(EMatchState MatchState)
{
	CurrentMatchState = MatchState;
}

void ATanksGameState::SetWinnerTeam(ETeam Winner)
{
	WinnerTeam = Winner;
}
