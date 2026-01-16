// FootballHUD.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FootballHUD.generated.h"

UCLASS()
class FOOTBALL7V7_API AFootballHUD : public AHUD
{
    GENERATED_BODY()

public:
    virtual void DrawHUD() override;
};
