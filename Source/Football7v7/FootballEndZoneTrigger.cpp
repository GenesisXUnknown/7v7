// FootballEndZoneTrigger.cpp
#include "FootballEndZoneTrigger.h"
#include "FootballCharacter.h"
#include "FootballGameMode.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

AFootballEndZoneTrigger::AFootballEndZoneTrigger()
{
    PrimaryActorTick.bCanEverTick = false;

    TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
    TriggerVolume->SetBoxExtent(FVector(500.f, 2500.f, 200.f));
    TriggerVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    TriggerVolume->SetCollisionResponseToAllChannels(ECR_Overlap);
    TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AFootballEndZoneTrigger::OnTriggerOverlap);
    RootComponent = TriggerVolume;

    ScoringTeam = ETeam::Offense;
}

void AFootballEndZoneTrigger::OnTriggerOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                               bool bFromSweep, const FHitResult& SweepResult)
{
    AFootballCharacter* Character = Cast<AFootballCharacter>(OtherActor);
    if (!Character || !Character->HasBall())
    {
        return;
    }

    AFootballGameMode* GameMode = Cast<AFootballGameMode>(UGameplayStatics::GetGameMode(this));
    if (GameMode && GameMode->GetPlayState() == EPlayState::PostSnap)
    {
        UE_LOG(LogTemp, Log, TEXT("TOUCHDOWN! Scoring Team: %s"),
               ScoringTeam == ETeam::Offense ? TEXT("Offense") : TEXT("Defense"));
        GameMode->OnTouchdown(ScoringTeam);
    }
}
