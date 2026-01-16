// FootballHUD.cpp
#include "FootballHUD.h"
#include "FootballGameMode.h"
#include "Engine/Canvas.h"
#include "Kismet/GameplayStatics.h"

void AFootballHUD::DrawHUD()
{
    Super::DrawHUD();

    AFootballGameMode* GameMode = Cast<AFootballGameMode>(UGameplayStatics::GetGameMode(this));
    if (!GameMode)
    {
        return;
    }

    // Draw scores
    FString OffenseText = FString::Printf(TEXT("Offense: %d"), GameMode->GetOffenseScore());
    FString DefenseText = FString::Printf(TEXT("Defense: %d"), GameMode->GetDefenseScore());

    // Draw play state
    FString StateText;
    switch (GameMode->GetPlayState())
    {
        case EPlayState::PreSnap:
            StateText = TEXT("PRE-SNAP (Press SPACE to Snap)");
            break;
        case EPlayState::PostSnap:
            StateText = TEXT("PLAY IN PROGRESS (1-4 to Pass)");
            break;
        case EPlayState::PlayOver:
            StateText = TEXT("PLAY OVER (Resetting...)");
            break;
    }

    // Draw to screen
    float YOffset = 50.f;
    DrawText(OffenseText, FLinearColor::Green, 50.f, YOffset, nullptr, 1.5f);
    YOffset += 30.f;
    DrawText(DefenseText, FLinearColor::Red, 50.f, YOffset, nullptr, 1.5f);
    YOffset += 30.f;
    DrawText(StateText, FLinearColor::White, 50.f, YOffset, nullptr, 1.2f);
}
