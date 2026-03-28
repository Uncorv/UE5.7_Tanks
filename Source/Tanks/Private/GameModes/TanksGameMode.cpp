#include "GameModes/TanksGameMode.h"
#include "GameModes/TanksGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Pawns/TankPawn.h"

void ATanksGameMode::BeginPlay()
{
	StartMatchFlow();
}

void ATanksGameMode::StartMatchFlow()
{
	if (CurrentMatchState == EMatchState::WaitingToStart)
	{
		CurrentMatchState = EMatchState::InProgress;
		FindParticipants();
	}

	UpdateGameState();
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
	CheckWinCondition();
}

void ATanksGameMode::CheckWinCondition()
{
	if (!bIsBaseAliveTeamA)
	{
		EndMatch(ETeam::TeamB);
	}
	else if (!bIsBaseAliveTeamB)
	{
		EndMatch(ETeam::TeamA);
	}
}

void ATanksGameMode::FindParticipants()
{
	TArray <AActor *> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(this, ATankPawn::StaticClass(), FoundActors);
	if (!FoundActors.IsEmpty())
	{
		for (auto *Actor : FoundActors)
		{
			ATankPawn *TP = Cast<ATankPawn>(Actor);
			if (TP)
			{
				if (TP->GetTeam() == ETeam::TeamA)
				{
					++AliveTanksTeamA;
				}
				else if (TP->GetTeam() == ETeam::TeamB)
				{
					++AliveTanksTeamB;
				}
				else
				{
					continue;
				}
			}
		}
	}
	UpdateGameState();
}

void ATanksGameMode::EndMatch(ETeam Winner)
{
	CurrentMatchState = EMatchState::Finished;
	WinnerTeam = Winner;

	UpdateGameState();
}

void ATanksGameMode::UpdateGameState()
{
	ATanksGameState *TanksGameState = GetGameState<ATanksGameState>();
	if (TanksGameState)
	{
		TanksGameState->SetAliveTanksTeamA(AliveTanksTeamA);
		TanksGameState->SetAliveTanksTeamB(AliveTanksTeamB);
		TanksGameState->SetIsBaseAliveTeamA(bIsBaseAliveTeamA);
		TanksGameState->SetIsBaseAliveTeamB(bIsBaseAliveTeamB);
		TanksGameState->SetCurrentMatchState(CurrentMatchState);
		TanksGameState->SetWinnerTeam(WinnerTeam);
	}
}