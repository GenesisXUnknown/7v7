// FootballPlayerController.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FootballPlayerController.generated.h"

class AFootballCharacter;

UCLASS()
class FOOTBALL7V7_API AFootballPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    AFootballPlayerController();

protected:
    virtual void SetupInputComponent() override;
    virtual void BeginPlay() override;

    // Input actions
    void OnSnapBall();
    void OnPassToReceiver1();
    void OnPassToReceiver2();
    void OnPassToReceiver3();
    void OnPassToReceiver4();

    void PassToReceiver(int32 ReceiverIndex);

    UPROPERTY()
    AFootballCharacter* ControlledQB;
};
