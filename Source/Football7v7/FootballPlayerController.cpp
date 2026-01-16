// FootballPlayerController.cpp
#include "FootballPlayerController.h"
#include "FootballCharacter.h"
#include "FootballGameMode.h"
#include "Kismet/GameplayStatics.h"

AFootballPlayerController::AFootballPlayerController()
{
    ControlledQB = nullptr;
}

void AFootballPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // Get controlled QB
    ControlledQB = Cast<AFootballCharacter>(GetPawn());
}

void AFootballPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (InputComponent)
    {
        // Snap
        InputComponent->BindAction("Snap", IE_Pressed, this, &AFootballPlayerController::OnSnapBall);

        // Pass to receivers
        InputComponent->BindAction("Pass1", IE_Pressed, this, &AFootballPlayerController::OnPassToReceiver1);
        InputComponent->BindAction("Pass2", IE_Pressed, this, &AFootballPlayerController::OnPassToReceiver2);
        InputComponent->BindAction("Pass3", IE_Pressed, this, &AFootballPlayerController::OnPassToReceiver3);
        InputComponent->BindAction("Pass4", IE_Pressed, this, &AFootballPlayerController::OnPassToReceiver4);

        // Movement (standard)
        InputComponent->BindAxis("MoveForward", ControlledQB, &AFootballCharacter::MoveForward);
        InputComponent->BindAxis("MoveRight", ControlledQB, &AFootballCharacter::MoveRight);
        InputComponent->BindAxis("Turn", this, &APlayerController::AddYawInput);
        InputComponent->BindAxis("LookUp", this, &APlayerController::AddPitchInput);
    }
}

void AFootballPlayerController::OnSnapBall()
{
    AFootballGameMode* GameMode = Cast<AFootballGameMode>(UGameplayStatics::GetGameMode(this));
    if (GameMode)
    {
        GameMode->SnapBall();
    }
}

void AFootballPlayerController::OnPassToReceiver1() { PassToReceiver(0); }
void AFootballPlayerController::OnPassToReceiver2() { PassToReceiver(1); }
void AFootballPlayerController::OnPassToReceiver3() { PassToReceiver(2); }
void AFootballPlayerController::OnPassToReceiver4() { PassToReceiver(3); }

void AFootballPlayerController::PassToReceiver(int32 ReceiverIndex)
{
    if (!ControlledQB)
    {
        return;
    }

    ControlledQB->ThrowPassToReceiver(ReceiverIndex);
}
