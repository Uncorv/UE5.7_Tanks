#include "UI/TankHUD.h"
#include "Controllers/TankPlayerController.h"
#include "Engine/Canvas.h"
#include "GameModes/TanksGameState.h"
#include "Pawns/TankPawn.h"

void ATankHUD::BeginPlay()
{
	Super::BeginPlay();

	Font = GEngine->GetMediumFont();
}


void ATankHUD::DrawHUD()
{
	Super::DrawHUD();

	ATankPlayerController *PC = Cast<ATankPlayerController>(GetOwningPlayerController());
	if (PC)
	{
		ATankPawn *TP = PC->GetPawn<ATankPawn>();

		if (TP)
		{
			FString CanFireText;
			FLinearColor CanFireColor;
			if (TP->CanFire())
			{
				CanFireText = FString::Printf(TEXT("Ready to fire!"));
				CanFireColor = FLinearColor::Green;
			}
			else
			{
				CanFireText = FString::Printf(TEXT("Reloading"));
				CanFireColor = FLinearColor::Black;
			}

			FString HPText = FString::Printf(TEXT("Health: %.1f"), TP->GetCurrentHealth());
			FLinearColor HPColor = FLinearColor::Red;
			float HPTextWidth, HPTextHeight;
			Canvas->StrLen(Font, HPText, HPTextWidth, HPTextHeight);
			float HPX = (Canvas->SizeX - HPTextWidth) / 2;
			float HPY = Canvas->SizeY - 40.f;
			DrawText(HPText, HPColor, HPX, HPY, Font, 2.f);

			float CanFireTextWidth, CanFireTextHeight;
			Canvas->StrLen(Font, CanFireText, CanFireTextWidth, CanFireTextHeight);
			float CanFireX = (Canvas->SizeX - CanFireTextWidth) / 2;
			float CanFireY = HPY - 40.f;
			DrawText(CanFireText, CanFireColor, CanFireX, CanFireY, Font, 2.f);
		}
	}

	ATanksGameState *GS = GetWorld()->GetGameState<ATanksGameState>();
	if (GS)
	{
		FString MembersTeamAText = FString::Printf(TEXT("Tanks in team A: %i"), GS->GetAliveTanksTeamA());
		FLinearColor MembersTeamAColor = FLinearColor::Blue;
		float MembersTeamAX = 0;
		float MembersTeamAY = 40.f;
		DrawText(MembersTeamAText, MembersTeamAColor, MembersTeamAX, MembersTeamAY, (UFont*)0, 2.f);

		FString MembersTeamBText = FString::Printf(TEXT("Tanks in team B: %i"), GS->GetAliveTanksTeamB());
		FLinearColor MembersTeamBColor = FLinearColor::Red;
		float MembersTeamBX = MembersTeamAX;
		float MembersTeamBY = MembersTeamAY + 40.f;
		DrawText(MembersTeamBText, MembersTeamBColor, MembersTeamBX, MembersTeamBY, (UFont*)0, 2.f);

		if (GS->GetCurrentMatchState() == EMatchState::Finished)
		{
			FString WinnerTeamText;
			FLinearColor WinnerTeamColor = FLinearColor::Yellow;
			if (GS->GetWinnerTeam() == ETeam::TeamA)
			{
				WinnerTeamText = FString::Printf(TEXT("Team A Won!"));
			}
			else if (GS->GetWinnerTeam() == ETeam::TeamB)
			{
				WinnerTeamText = FString::Printf(TEXT("Team B Won!"));
			}

			float WinnerTeamTextWidth, WinnerTeamTextHeight;
			Canvas->StrLen(Font, WinnerTeamText, WinnerTeamTextWidth, WinnerTeamTextHeight);
			float WinnerTeamTextX = (Canvas->SizeX - WinnerTeamTextWidth) / 2;
			float WinnerTeamTextY = Canvas->SizeY / 4;
			DrawText(WinnerTeamText, WinnerTeamColor, WinnerTeamTextX, WinnerTeamTextY, Font, 2.f);
		}
	}
}
