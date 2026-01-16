// FootballTypes.h
#pragma once

#include "CoreMinimal.h"
#include "FootballTypes.generated.h"

UENUM(BlueprintType)
enum class EPlayState : uint8
{
    PreSnap     UMETA(DisplayName = "Pre-Snap"),
    PostSnap    UMETA(DisplayName = "Post-Snap"),
    PlayOver    UMETA(DisplayName = "Play Over")
};

UENUM(BlueprintType)
enum class ETeam : uint8
{
    Offense     UMETA(DisplayName = "Offense"),
    Defense     UMETA(DisplayName = "Defense"),
    None        UMETA(DisplayName = "None")
};

UENUM(BlueprintType)
enum class EPosition : uint8
{
    // Offense
    QB          UMETA(DisplayName = "Quarterback"),
    RB          UMETA(DisplayName = "Running Back"),
    WR1         UMETA(DisplayName = "Wide Receiver 1"),
    WR2         UMETA(DisplayName = "Wide Receiver 2"),
    WR3         UMETA(DisplayName = "Wide Receiver 3"),
    TE          UMETA(DisplayName = "Tight End"),
    OL          UMETA(DisplayName = "Offensive Line"),

    // Defense
    DL          UMETA(DisplayName = "Defensive Line"),
    LB          UMETA(DisplayName = "Linebacker"),
    CB1         UMETA(DisplayName = "Cornerback 1"),
    CB2         UMETA(DisplayName = "Cornerback 2"),
    S1          UMETA(DisplayName = "Safety 1"),
    S2          UMETA(DisplayName = "Safety 2"),
    Rover       UMETA(DisplayName = "Rover"),

    None        UMETA(DisplayName = "None")
};
