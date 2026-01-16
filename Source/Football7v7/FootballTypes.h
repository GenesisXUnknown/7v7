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
    // Offense (11 positions for 11v11)
    QB          UMETA(DisplayName = "Quarterback"),
    RB          UMETA(DisplayName = "Running Back"),
    FB          UMETA(DisplayName = "Fullback"),
    WR1         UMETA(DisplayName = "Wide Receiver 1"),
    WR2         UMETA(DisplayName = "Wide Receiver 2"),
    WR3         UMETA(DisplayName = "Wide Receiver 3"),
    TE          UMETA(DisplayName = "Tight End"),
    LT          UMETA(DisplayName = "Left Tackle"),
    LG          UMETA(DisplayName = "Left Guard"),
    C           UMETA(DisplayName = "Center"),
    RG          UMETA(DisplayName = "Right Guard"),
    RT          UMETA(DisplayName = "Right Tackle"),

    // Defense (11 positions for 11v11)
    DE1         UMETA(DisplayName = "Defensive End 1"),
    DE2         UMETA(DisplayName = "Defensive End 2"),
    DT1         UMETA(DisplayName = "Defensive Tackle 1"),
    DT2         UMETA(DisplayName = "Defensive Tackle 2"),
    MLB         UMETA(DisplayName = "Middle Linebacker"),
    OLB1        UMETA(DisplayName = "Outside Linebacker 1"),
    OLB2        UMETA(DisplayName = "Outside Linebacker 2"),
    CB1         UMETA(DisplayName = "Cornerback 1"),
    CB2         UMETA(DisplayName = "Cornerback 2"),
    FS          UMETA(DisplayName = "Free Safety"),
    SS          UMETA(DisplayName = "Strong Safety"),

    // Legacy 7v7 positions (kept for backward compatibility)
    OL          UMETA(DisplayName = "Offensive Line (7v7)"),
    DL          UMETA(DisplayName = "Defensive Line (7v7)"),
    LB          UMETA(DisplayName = "Linebacker (7v7)"),
    S1          UMETA(DisplayName = "Safety 1 (7v7)"),
    S2          UMETA(DisplayName = "Safety 2 (7v7)"),
    Rover       UMETA(DisplayName = "Rover (7v7)"),

    None        UMETA(DisplayName = "None")
};
