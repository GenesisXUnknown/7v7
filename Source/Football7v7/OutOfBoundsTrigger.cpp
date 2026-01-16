// OutOfBoundsTrigger.cpp
#include "OutOfBoundsTrigger.h"
#include "FootballCharacter.h"
#include "FootballGameMode.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

AOutOfBoundsTrigger::AOutOfBoundsTrigger()
{
	PrimaryActorTick.bCanEverTick = false;

	BoundaryVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("BoundaryVolume"));
	BoundaryVolume->SetBoxExtent(FVector(50.f, 5000.f, 200.f));
	BoundaryVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoundaryVolume->SetCollisionResponseToAllChannels(ECR_Overlap);
	BoundaryVolume->OnComponentBeginOverlap.AddDynamic(this, &AOutOfBoundsTrigger::OnBoundaryOverlap);
	RootComponent = BoundaryVolume;
}

void AOutOfBoundsTrigger::OnBoundaryOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
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
		UE_LOG(LogTemp, Log, TEXT("OUT OF BOUNDS! Ball carrier: %s"), *Character->GetName());
		GameMode->OnPlayOver();
	}
}
