// FootballCharacter.cpp
#include "FootballCharacter.h"
#include "FootballBall.h"
#include "FootballGameMode.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"

AFootballCharacter::AFootballCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    Team = ETeam::None;
    Position = EPosition::None;
    bHasBall = false;
    PassSpeed = 2000.f;
    PassLeadTime = 0.5f;
    DefensePursuitSpeed = 400.f;
    bIsThrowingAnimation = false;
    bIsCatchingAnimation = false;
    bIsTackledAnimation = false;

    // Enable overlap events
    GetCapsuleComponent()->SetGenerateOverlapEvents(true);
    GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AFootballCharacter::OnOverlapBegin);
}

void AFootballCharacter::BeginPlay()
{
    Super::BeginPlay();

    CaptureSpawnTransform();

    // QB gathers eligible receivers
    if (Position == EPosition::QB)
    {
        GatherEligibleReceivers();
    }
}

void AFootballCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Simple defensive AI
    if (Team == ETeam::Defense)
    {
        UpdateDefenseAI(DeltaTime);
    }
}

void AFootballCharacter::CaptureSpawnTransform()
{
    SpawnTransform = GetActorTransform();
}

void AFootballCharacter::ResetToSpawnTransform()
{
    SetActorTransform(SpawnTransform);
    GetCharacterMovement()->Velocity = FVector::ZeroVector;
}

void AFootballCharacter::MoveForward(float Value)
{
    if (Controller && Value != 0.f)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, Value);
    }
}

void AFootballCharacter::MoveRight(float Value)
{
    if (Controller && Value != 0.f)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        AddMovementInput(Direction, Value);
    }
}

void AFootballCharacter::GatherEligibleReceivers()
{
    EligibleReceivers.Empty();

    TArray<AActor*> FoundCharacters;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFootballCharacter::StaticClass(), FoundCharacters);

    // Gather offensive receivers (RB, WR1, WR2, WR3, TE) - up to 4
    TArray<EPosition> EligiblePositions = { EPosition::RB, EPosition::WR1, EPosition::WR2, EPosition::WR3 };

    for (EPosition Pos : EligiblePositions)
    {
        for (AActor* Actor : FoundCharacters)
        {
            AFootballCharacter* Character = Cast<AFootballCharacter>(Actor);
            if (Character && Character->Team == ETeam::Offense && Character->Position == Pos)
            {
                EligibleReceivers.Add(Character);
                break;
            }
        }
    }

    UE_LOG(LogTemp, Log, TEXT("QB found %d eligible receivers"), EligibleReceivers.Num());
}

void AFootballCharacter::ThrowPassToReceiver(int32 ReceiverIndex)
{
    if (!bHasBall)
    {
        return;
    }

    if (!EligibleReceivers.IsValidIndex(ReceiverIndex))
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid receiver index: %d"), ReceiverIndex);
        return;
    }

    AFootballCharacter* Receiver = EligibleReceivers[ReceiverIndex];
    if (!Receiver)
    {
        return;
    }

    AFootballGameMode* GameMode = Cast<AFootballGameMode>(UGameplayStatics::GetGameMode(this));
    if (!GameMode)
    {
        return;
    }

    AFootballBall* Ball = GameMode->GetBall();
    if (!Ball)
    {
        return;
    }

    // Calculate lead target
    FVector ReceiverVelocity = Receiver->GetVelocity();
    FVector TargetLocation = Receiver->GetActorLocation() + (ReceiverVelocity * PassLeadTime);

    // Detach and throw
    Ball->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
    bHasBall = false;

    FVector Direction = (TargetLocation - Ball->GetActorLocation()).GetSafeNormal();
    Ball->ThrowBall(Direction * PassSpeed);

    UE_LOG(LogTemp, Log, TEXT("QB threw pass to receiver %d"), ReceiverIndex);
}

void AFootballCharacter::UpdateDefenseAI(float DeltaTime)
{
    AFootballGameMode* GameMode = Cast<AFootballGameMode>(UGameplayStatics::GetGameMode(this));
    if (!GameMode || GameMode->GetPlayState() != EPlayState::PostSnap)
    {
        return;
    }

    // Find ball carrier
    TArray<AActor*> FoundCharacters;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFootballCharacter::StaticClass(), FoundCharacters);

    AFootballCharacter* BallCarrier = nullptr;
    for (AActor* Actor : FoundCharacters)
    {
        AFootballCharacter* Character = Cast<AFootballCharacter>(Actor);
        if (Character && Character->HasBall())
        {
            BallCarrier = Character;
            break;
        }
    }

    if (!BallCarrier)
    {
        return;
    }

    // Simple pursuit: move toward ball carrier
    FVector Direction = (BallCarrier->GetActorLocation() - GetActorLocation()).GetSafeNormal();
    AddMovementInput(Direction, 1.f);
}

void AFootballCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                        bool bFromSweep, const FHitResult& SweepResult)
{
    AFootballCharacter* OtherCharacter = Cast<AFootballCharacter>(OtherActor);
    if (!OtherCharacter)
    {
        return;
    }

    // Tackle detection: defensive player overlaps ball carrier
    if (Team == ETeam::Defense && OtherCharacter->Team == ETeam::Offense && OtherCharacter->HasBall())
    {
        UE_LOG(LogTemp, Log, TEXT("TACKLE! Play Over"));

        AFootballGameMode* GameMode = Cast<AFootballGameMode>(UGameplayStatics::GetGameMode(this));
        if (GameMode)
        {
            GameMode->OnPlayOver();
        }
    }
}
