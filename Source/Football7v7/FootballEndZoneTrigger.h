// FootballEndZoneTrigger.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FootballTypes.h"
#include "FootballEndZoneTrigger.generated.h"

class UBoxComponent;

UCLASS()
class FOOTBALL7V7_API AFootballEndZoneTrigger : public AActor
{
    GENERATED_BODY()

public:
    AFootballEndZoneTrigger();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Football")
    ETeam ScoringTeam;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UBoxComponent* TriggerVolume;

    UFUNCTION()
    void OnTriggerOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                          bool bFromSweep, const FHitResult& SweepResult);
};
