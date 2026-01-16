// FootballCharacter.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FootballTypes.h"
#include "FootballCharacter.generated.h"

class AFootballBall;

UCLASS()
class FOOTBALL7V7_API AFootballCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AFootballCharacter();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    // Team and position
    UFUNCTION(BlueprintPure, Category = "Football")
    ETeam GetTeam() const { return Team; }

    UFUNCTION(BlueprintCallable, Category = "Football")
    void SetTeam(ETeam NewTeam) { Team = NewTeam; }

    UFUNCTION(BlueprintPure, Category = "Football")
    EPosition GetPosition() const { return Position; }

    UFUNCTION(BlueprintCallable, Category = "Football")
    void SetPosition(EPosition NewPosition) { Position = NewPosition; }

    // Ball carrier
    UFUNCTION(BlueprintPure, Category = "Football")
    bool HasBall() const { return bHasBall; }

    UFUNCTION(BlueprintCallable, Category = "Football")
    void SetHasBall(bool bNewHasBall) { bHasBall = bNewHasBall; }

    // Passing
    UFUNCTION(BlueprintCallable, Category = "Football")
    void ThrowPassToReceiver(int32 ReceiverIndex);

    // Reset
    UFUNCTION(BlueprintCallable, Category = "Football")
    void CaptureSpawnTransform();

    UFUNCTION(BlueprintCallable, Category = "Football")
    void ResetToSpawnTransform();

    // Movement (called from PlayerController)
    void MoveForward(float Value);
    void MoveRight(float Value);

    // Eligible receivers (for QB)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Football")
    TArray<AFootballCharacter*> EligibleReceivers;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Football")
    ETeam Team;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Football")
    EPosition Position;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Football")
    bool bHasBall;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Football")
    float PassSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Football")
    float PassLeadTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Football")
    float DefensePursuitSpeed;

    FTransform SpawnTransform;

    void GatherEligibleReceivers();
    void UpdateDefenseAI(float DeltaTime);

    // Overlap detection for tackling
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                        bool bFromSweep, const FHitResult& SweepResult);
};
