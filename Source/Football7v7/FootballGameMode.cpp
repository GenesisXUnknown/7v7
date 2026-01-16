// FootballGameMode.cpp
#include "FootballGameMode.h"
#include "FootballCharacter.h"
#include "FootballBall.h"
#include "FootballPlayerController.h"
#include "FootballHUD.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

AFootballGameMode::AFootballGameMode()
{
    PlayerControllerClass = AFootballPlayerController::StaticClass();
    DefaultPawnClass = AFootballCharacter::StaticClass();
    HUDClass = AFootballHUD::StaticClass();

    CurrentPlayState = EPlayState::PreSnap;
    OffenseScore = 0;
    DefenseScore = 0;
    LineOfScrimmage = FVector(0.f, 0.f, 100.f);
    ResetDelay = 0.75f;
}

void AFootballGameMode::BeginPlay()
{
    Super::BeginPlay();

    GatherAllPlayers();

    // Find ball in level
    TArray<AActor*> FoundBalls;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFootballBall::StaticClass(), FoundBalls);
    if (FoundBalls.Num() > 0)
    {
        Ball = Cast<AFootballBall>(FoundBalls[0]);
        if (Ball)
        {
            Ball->SetActorLocation(LineOfScrimmage);
        }
    }
}

void AFootballGameMode::GatherAllPlayers()
{
    AllPlayers.Empty();

    TArray<AActor*> FoundCharacters;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFootballCharacter::StaticClass(), FoundCharacters);

    for (AActor* Actor : FoundCharacters)
    {
        AFootballCharacter* Character = Cast<AFootballCharacter>(Actor);
        if (Character)
        {
            AllPlayers.Add(Character);
            Character->CaptureSpawnTransform();
        }
    }
}

void AFootballGameMode::SnapBall()
{
    if (CurrentPlayState != EPlayState::PreSnap)
    {
        return;
    }

    if (!Ball)
    {
        UE_LOG(LogTemp, Warning, TEXT("SnapBall: Ball not found"));
        return;
    }

    // Find QB
    AFootballCharacter* QB = nullptr;
    for (AFootballCharacter* Player : AllPlayers)
    {
        if (Player && Player->GetTeam() == ETeam::Offense && Player->GetPosition() == EPosition::QB)
        {
            QB = Player;
            break;
        }
    }

    if (!QB)
    {
        UE_LOG(LogTemp, Warning, TEXT("SnapBall: QB not found"));
        return;
    }

    // Attach ball to QB
    Ball->AttachToCharacter(QB);
    QB->SetHasBall(true);

    CurrentPlayState = EPlayState::PostSnap;

    UE_LOG(LogTemp, Log, TEXT("Ball snapped to QB"));
}

void AFootballGameMode::OnPlayOver()
{
    if (CurrentPlayState == EPlayState::PlayOver)
    {
        return;
    }

    CurrentPlayState = EPlayState::PlayOver;

    UE_LOG(LogTemp, Log, TEXT("Play Over - Resetting in %.2f seconds"), ResetDelay);

    GetWorldTimerManager().SetTimer(ResetTimerHandle, this, &AFootballGameMode::ResetPlay, ResetDelay, false);
}

void AFootballGameMode::OnTouchdown(ETeam ScoringTeam)
{
    if (ScoringTeam == ETeam::Offense)
    {
        OffenseScore += 7;
        UE_LOG(LogTemp, Log, TEXT("TOUCHDOWN! Offense Score: %d"), OffenseScore);
    }
    else if (ScoringTeam == ETeam::Defense)
    {
        DefenseScore += 7;
        UE_LOG(LogTemp, Log, TEXT("TOUCHDOWN! Defense Score: %d"), DefenseScore);
    }

    OnPlayOver();
}

void AFootballGameMode::ResetPlay()
{
    UE_LOG(LogTemp, Log, TEXT("Resetting Play"));

    // Reset all players to spawn positions
    for (AFootballCharacter* Player : AllPlayers)
    {
        if (Player)
        {
            Player->ResetToSpawnTransform();
            Player->SetHasBall(false);
        }
    }

    // Reset ball
    if (Ball)
    {
        Ball->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        Ball->SetActorLocation(LineOfScrimmage);
        Ball->ResetBall();
    }

    CurrentPlayState = EPlayState::PreSnap;
}
