// FootballGameMode.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FootballTypes.h"
#include "FootballGameMode.generated.h"

class AFootballCharacter;
class AFootballBall;

UCLASS()
class FOOTBALL7V7_API AFootballGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    AFootballGameMode();

    virtual void BeginPlay() override;

    // Play state management
    UFUNCTION(BlueprintCallable, Category = "Football")
    void SnapBall();

    UFUNCTION(BlueprintCallable, Category = "Football")
    void OnPlayOver();

    UFUNCTION(BlueprintCallable, Category = "Football")
    void OnTouchdown(ETeam ScoringTeam);

    UFUNCTION(BlueprintPure, Category = "Football")
    EPlayState GetPlayState() const { return CurrentPlayState; }

    UFUNCTION(BlueprintPure, Category = "Football")
    int32 GetOffenseScore() const { return OffenseScore; }

    UFUNCTION(BlueprintPure, Category = "Football")
    int32 GetDefenseScore() const { return DefenseScore; }

    UFUNCTION(BlueprintPure, Category = "Football")
    AFootballBall* GetBall() const { return Ball; }

    // Line of scrimmage
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Football")
    FVector LineOfScrimmage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Football")
    float ResetDelay;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Football")
    EPlayState CurrentPlayState;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Football")
    int32 OffenseScore;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Football")
    int32 DefenseScore;

    UPROPERTY()
    AFootballBall* Ball;

    UPROPERTY()
    TArray<AFootballCharacter*> AllPlayers;

    FTimerHandle ResetTimerHandle;

    void GatherAllPlayers();
    void ResetPlay();
};
