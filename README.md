# Football 7v7 - Madden-lite Prototype

A minimal, playable 7v7 football game prototype built in Unreal Engine 5 with C++.

## Features

- **Play States**: PreSnap → PostSnap → PlayOver flow
- **Snap Mechanic**: Snap ball to QB (Space Bar)
- **Passing System**: QB can pass to 4 eligible receivers (Keys 1-4)
- **Ball Physics**: Projectile-based passing with catching on overlap
- **Tackling**: Defensive overlap with ball carrier ends the play
- **Touchdown Detection**: End zone triggers increment scores and reset play
- **Simple AI**: Defense pursues ball carrier during PostSnap
- **Live HUD**: Shows scores and current play state

## Tech Stack

- **Engine**: Unreal Engine 5.3
- **Language**: C++
- **Modules**: Core, Engine, AIModule

## Project Structure

```
Football7v7/
├── Config/                      # Engine configuration files
│   ├── DefaultEngine.ini
│   ├── DefaultGame.ini
│   ├── DefaultInput.ini
│   └── DefaultEditor.ini
├── Content/                     # Game assets (created in Editor)
│   └── Maps/
│       └── FootballField        # Main gameplay map (create in Editor)
├── Source/
│   ├── Football7v7.Target.cs
│   ├── Football7v7Editor.Target.cs
│   └── Football7v7/
│       ├── Football7v7.Build.cs
│       ├── Football7v7.h/.cpp   # Module files
│       ├── FootballTypes.h      # Enums (PlayState, Team, Position)
│       ├── FootballGameMode.h/.cpp
│       ├── FootballPlayerController.h/.cpp
│       ├── FootballCharacter.h/.cpp
│       ├── FootballBall.h/.cpp
│       ├── FootballEndZoneTrigger.h/.cpp
│       └── FootballHUD.h/.cpp
└── Football7v7.uproject
```

## Getting Started

### Prerequisites

- Unreal Engine 5.3 or later
- Visual Studio 2022 (Windows) or Xcode (Mac) or compatible C++ compiler
- Git

### Setup Instructions

1. **Clone the repository**:
   ```bash
   git clone <repository-url>
   cd 7v7
   ```

2. **Generate project files**:
   - Right-click `Football7v7.uproject` → "Generate Visual Studio project files"
   - Or use command line: `UnrealBuildTool -projectfiles -project="Football7v7.uproject" -game -engine`

3. **Open in Unreal Editor**:
   - Double-click `Football7v7.uproject` to launch the editor
   - Compile C++ code when prompted

4. **Create the Football Field Map**:
   - File → New Level → Empty Level
   - Add floor plane (10,000 x 5,000 units minimum)
   - Add lighting (Directional Light + Sky Light)
   - Save as `Content/Maps/FootballField`

5. **Place Game Actors** (see Editor Setup below)

6. **Play**:
   - Click Play (PIE) or press Alt+P

### Editor Setup

#### 1. Verify Project Settings

**Edit → Project Settings → Maps & Modes**:
- Default GameMode: `FootballGameMode`
- Default Pawn Class: `FootballCharacter`
- Player Controller Class: `FootballPlayerController`
- HUD Class: `FootballHUD`

**Edit → Project Settings → Input** (already configured):
- Action Mappings:
  - `Snap` → Space Bar
  - `Pass1` → 1
  - `Pass2` → 2
  - `Pass3` → 3
  - `Pass4` → 4
- Axis Mappings:
  - `MoveForward` → W/S
  - `MoveRight` → A/D
  - `Turn` → Mouse X
  - `LookUp` → Mouse Y

#### 2. Place the Ball

1. Drag `FootballBall` into the level
2. Position at **(0, 0, 100)**
3. Assign a football or sphere mesh to the BallMesh component
4. **Only place ONE ball in the level**

#### 3. Place 14 Characters (7 Offense + 7 Defense)

**Example Formation**:

**Offense**:
| Position | Location (X, Y, Z) | Team | Position Enum | Auto Possess |
|----------|-------------------|------|---------------|--------------|
| QB | (0, 0, 90) | Offense | QB | **Player 0** |
| RB | (-100, 0, 90) | Offense | RB | Disabled |
| WR1 | (0, -300, 90) | Offense | WR1 | Disabled |
| WR2 | (0, 300, 90) | Offense | WR2 | Disabled |
| WR3 | (0, -500, 90) | Offense | WR3 | Disabled |
| TE | (0, 150, 90) | Offense | TE | Disabled |
| OL | (50, 0, 90) | Offense | OL | Disabled |

**Defense**:
| Position | Location (X, Y, Z) | Team | Position Enum | Auto Possess |
|----------|-------------------|------|---------------|--------------|
| DL | (300, 0, 90) | Defense | DL | Disabled |
| LB | (400, 0, 90) | Defense | LB | Disabled |
| CB1 | (300, -300, 90) | Defense | CB1 | Disabled |
| CB2 | (300, 300, 90) | Defense | CB2 | Disabled |
| S1 | (500, -200, 90) | Defense | S1 | Disabled |
| S2 | (500, 200, 90) | Defense | S2 | Disabled |
| Rover | (600, 0, 90) | Defense | Rover | Disabled |

**For each character**:
- Drag `FootballCharacter` into level
- Set **Team** (Offense or Defense)
- Set **Position** (QB, RB, WR1, etc.)
- **QB ONLY**: Set **Auto Possess Player** to **Player 0**

#### 4. Place End Zone Triggers

1. Place 2x `FootballEndZoneTrigger` actors
2. **Offense End Zone**:
   - Position: **(3000, 0, 100)**
   - Scoring Team: `Offense`
3. **Defense End Zone** (optional):
   - Position: **(-3000, 0, 100)**
   - Scoring Team: `Defense`

#### 5. Set Line of Scrimmage

1. Select **World Settings** tab
2. Find **Game Mode Override** (`FootballGameMode`)
3. Set **Line of Scrimmage**: **(0, 0, 100)**

## Controls

| Input | Action |
|-------|--------|
| **WASD** | Move QB |
| **Mouse** | Look around |
| **Space Bar** | Snap ball (PreSnap only) |
| **1** | Pass to Receiver 1 (RB) |
| **2** | Pass to Receiver 2 (WR1) |
| **3** | Pass to Receiver 3 (WR2) |
| **4** | Pass to Receiver 4 (WR3) |

## Gameplay Flow

1. **PreSnap**: Press Space to snap ball to QB
2. **PostSnap**:
   - Move QB with WASD
   - Press 1-4 to throw to receivers
   - Receivers auto-catch on overlap
   - Defense pursues ball carrier
3. **Play Ends When**:
   - Defensive player tackles ball carrier (overlap)
   - Ball carrier reaches end zone (touchdown)
4. **Reset**: 0.75s delay, then returns to PreSnap

## Smoke Test Checklist

- [x] Snap ball attaches to QB
- [x] Pass to Receiver 1 (key 1)
- [x] Pass to Receiver 2 (key 2)
- [x] Pass to Receiver 3 (key 3)
- [x] Pass to Receiver 4 (key 4)
- [x] Receiver catches ball on overlap
- [x] Defense pursues ball carrier
- [x] Tackle ends play
- [x] Touchdown increments score
- [x] Reset returns to PreSnap with all players at spawn positions

## Code Overview

### Key Classes

- **FootballTypes.h**: Enums for PlayState, Team, Position
- **FootballGameMode**: Manages play state, scoring, snap, reset
- **FootballPlayerController**: Handles input binding and pass commands
- **FootballCharacter**: Player/AI character with team, position, movement, tackling
- **FootballBall**: Projectile actor with throw/catch/attach mechanics
- **FootballEndZoneTrigger**: Touchdown detection trigger volume
- **FootballHUD**: On-screen score and state display

### Architecture

- **No Replication**: Single-player only
- **No GAS/Advanced Systems**: Minimal C++ prototype
- **Blueprint-Friendly**: All properties exposed via UPROPERTY
- **Simple AI**: Defense uses AddMovementInput toward ball carrier

## Extending the Prototype

### Adding More Receivers

Edit `FootballCharacter::GatherEligibleReceivers()`:
```cpp
TArray<EPosition> EligiblePositions = { EPosition::RB, EPosition::WR1, EPosition::WR2, EPosition::TE };
```

### Adjusting Pass Physics

In `FootballCharacter`:
- `PassSpeed` (default: 2000.f)
- `PassLeadTime` (default: 0.5f)

In `FootballBall`:
- `ProjectileGravityScale` (default: 0.5f)
- `MaxSpeed` (default: 3000.f)

### Improving Defense AI

Replace `UpdateDefenseAI()` with:
- Behavior Trees (AIModule)
- Zone coverage logic
- Pursuit angles and interceptions

## Known Limitations

- No animations (characters slide)
- No play calling system
- No replays or camera cuts
- Single-player only
- Defense AI is extremely basic
- No out-of-bounds detection
- No play clock or downs system

## License

MIT License - See LICENSE file

## Contributing

This is a prototype/learning project. Feel free to fork and extend!

## Support

For issues or questions, please open an issue on GitHub.

---

**Built with Unreal Engine 5.3**
