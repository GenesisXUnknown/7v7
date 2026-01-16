# Football 7v7/11v11 - Complete Football Game

A complete, playable football game built in Unreal Engine 5 with C++. Supports both 7v7 and 11v11 gameplay with advanced features including animations, camera system, AI, UI, and formations.

## 🎮 Features

### Core Gameplay
- ✅ **Play States**: PreSnap → PostSnap → PlayOver state machine
- ✅ **Snap Mechanic**: Snap ball to QB (Space Bar)
- ✅ **Advanced Passing System**: QB can pass to 4 eligible receivers with lead targeting (Keys 1-4)
- ✅ **Ball Physics**: Projectile movement with gravity and catching mechanics
- ✅ **Tackling**: Defensive overlap detection ends play
- ✅ **Touchdown Detection**: End zone triggers with scoring system
- ✅ **Out of Bounds**: Boundary detection system
- ✅ **Play Reset**: Automatic reset to spawn positions after plays

### NEW: Advanced Features

#### 🎬 Camera System
- **Multiple Camera Angles**:
  - Behind QB (default gameplay camera)
  - Sideline view
  - End zone view
  - Skycam (overhead)
  - Ball follow camera
  - Replay camera
- **Smooth Camera Transitions**: Interpolated camera movement
- **Automatic Tracking**: Follows ball carrier or QB
- **Replay System**: Trigger instant replays with configurable duration

#### 🏃 Animation System
- **Animation Blueprint Support**: UFootballAnimInstance for character animations
- **Animation States**:
  - Speed and direction blending
  - Throwing animations
  - Catching animations
  - Tackled animations
  - Jump/falling states
- **Blueprint-Friendly**: All animation states exposed to Blueprints

#### 🤖 Behavior Tree AI
- **AI Controller**: AFootballAIController with perception system
- **Behavior Tree Tasks**:
  - Find Ball Carrier (BT Task)
  - Run Routes (8 route types: Go, Slant, Out, In, Post, Corner, Curl, Flat)
- **AI Perception**: Sight-based detection system
- **Smart Pursuit**: Defensive players intelligently pursue ball carrier

#### 🎨 Play Calling UI
- **UMG Widget System**: Play selection interface
- **Pre-Built Plays**: 4 offensive plays included
  - Four Verticals
  - Slants
  - HB Draw
  - Corners
- **Play Diagrams**: Support for play visualization
- **Route Data**: Receiver route information per play

#### 📐 Formation System
- **Data Asset Based**: UFormationData for easy formation creation
- **Pre-Built Formations**:
  - **Offense**: Pro Formation, Shotgun Spread
  - **Defense**: 4-3 Defense, 3-4 Defense
- **11v11 Support**: Full 22-player support
- **Position Management**: Relative positioning system

#### 🏈 11v11 Positions

**Offense (11 positions)**:
- QB (Quarterback)
- RB (Running Back), FB (Fullback)
- WR1, WR2, WR3 (Wide Receivers)
- TE (Tight End)
- LT, LG, C, RG, RT (Offensive Line)

**Defense (11 positions)**:
- DE1, DE2 (Defensive Ends)
- DT1, DT2 (Defensive Tackles)
- MLB (Middle Linebacker)
- OLB1, OLB2 (Outside Linebackers)
- CB1, CB2 (Cornerbacks)
- FS (Free Safety), SS (Strong Safety)

**Legacy 7v7 positions still supported for backward compatibility**

## 📁 Project Structure

```
Football7v7/
├── Config/                          # Engine configuration
│   ├── DefaultEngine.ini
│   ├── DefaultGame.ini
│   ├── DefaultInput.ini
│   └── DefaultEditor.ini
├── Content/                         # Game assets
│   └── Maps/
│       └── FootballField            # Main gameplay map
├── Source/
│   ├── Football7v7.Target.cs
│   ├── Football7v7Editor.Target.cs
│   └── Football7v7/
│       ├── Football7v7.Build.cs
│       ├── Football7v7.h/.cpp       # Module files
│       ├── FootballTypes.h          # Core enums
│       │
│       ├── FootballGameMode.h/.cpp  # Game state management
│       ├── FootballPlayerController.h/.cpp
│       ├── FootballCharacter.h/.cpp # Player/AI characters
│       ├── FootballBall.h/.cpp      # Ball physics
│       ├── FootballHUD.h/.cpp       # Score display
│       │
│       ├── FootballEndZoneTrigger.h/.cpp  # Touchdown detection
│       ├── OutOfBoundsTrigger.h/.cpp      # Boundary detection
│       │
│       ├── FootballAnimInstance.h/.cpp    # Animation system
│       ├── FootballCameraManager.h/.cpp   # Camera system
│       │
│       ├── FootballAIController.h/.cpp    # AI controller
│       ├── BTTask_FindBallCarrier.h/.cpp  # BT task
│       ├── BTTask_RunRoute.h/.cpp         # BT task
│       │
│       ├── PlayCallWidget.h/.cpp          # Play calling UI
│       └── FormationData.h/.cpp           # Formation system
└── Football7v7.uproject
```

## 🚀 Getting Started

### Prerequisites

- **Unreal Engine 5.3+**
- **Visual Studio 2022** (Windows) or **Xcode** (Mac)
- **Git**

### Installation

1. **Clone the repository**:
   ```bash
   git clone <repository-url>
   cd 7v7
   ```

2. **Generate project files**:
   - **Windows**: Right-click `Football7v7.uproject` → "Generate Visual Studio project files"
   - **Mac**: Right-click → "Generate Xcode project files"
   - **Linux**: `UnrealBuildTool -projectfiles -project="Football7v7.uproject"`

3. **Open in Unreal Editor**:
   - Double-click `Football7v7.uproject`
   - Allow C++ compilation when prompted

4. **Create a level** (see Quick Setup below)

5. **Press Play!**

## 🎯 Quick Setup (7v7 Mode)

### 1. Create Level

- File → New Level → Empty Level
- Add floor plane (scale: 100, 50, 1)
- Add Directional Light + Sky Light
- Save as `Content/Maps/FootballField`

### 2. Place Ball (1 actor)

- Place Classes → FootballBall at **(0, 0, 100)**
- Set Static Mesh to sphere/football mesh

### 3. Place QB (Player-Controlled)

- Place Classes → FootballCharacter at **(0, 0, 90)**
- Details:
  - Team: **Offense**
  - Position: **QB**
  - Auto Possess Player: **Player 0** ⚠️ CRITICAL

### 4. Place 4 Receivers (AI)

| Position | Location | Team | Position |
|----------|----------|------|----------|
| RB | (-100, 0, 90) | Offense | RB |
| WR1 | (0, -300, 90) | Offense | WR1 |
| WR2 | (0, 300, 90) | Offense | WR2 |
| WR3 | (0, -500, 90) | Offense | WR3 |

### 5. Place 7 Defenders (AI)

| Position | Location | Team | Position |
|----------|----------|------|----------|
| DL | (300, 0, 90) | Defense | DL |
| LB | (400, 0, 90) | Defense | LB |
| CB1 | (300, -300, 90) | Defense | CB1 |
| CB2 | (300, 300, 90) | Defense | CB2 |
| S1 | (500, -200, 90) | Defense | S1 |
| S2 | (500, 200, 90) | Defense | S2 |
| Rover | (600, 0, 90) | Defense | Rover |

### 6. Place End Zones (2 triggers)

- Offense End Zone at **(3000, 0, 100)** → Scoring Team: **Offense**
- Defense End Zone at **(-3000, 0, 100)** → Scoring Team: **Defense**

### 7. Place Out of Bounds Triggers (Optional)

- Place 2x OutOfBoundsTrigger on sidelines
- Set box extent to cover field length

### 8. Press Play (Alt+P)

## 🎮 Controls

| Key | Action |
|-----|--------|
| **WASD** | Move QB |
| **Mouse** | Look around |
| **Space** | Snap ball |
| **1** | Pass to Receiver 1 |
| **2** | Pass to Receiver 2 |
| **3** | Pass to Receiver 3 |
| **4** | Pass to Receiver 4 |

## 🏈 Advanced: 11v11 Setup

### Using Formation Data Assets

1. **Create Formation Data Asset**:
   - Content Browser → Right-click → Miscellaneous → Data Asset
   - Choose `FormationData`
   - Use pre-built formations or create custom

2. **Pre-Built Formations**:
   - **Offense**: Pro Formation, Shotgun Spread
   - **Defense**: 4-3, 3-4

3. **Spawn from Formation** (Blueprint or C++):
   ```cpp
   UFormationData* Formation = UFormationData::CreateProFormation();
   // Use Formation->PlayerSlots to spawn characters at positions
   ```

### 11v11 Position Guide

**Offensive Positions**:
- QB, RB, FB
- WR1, WR2, WR3, TE
- LT, LG, C, RG, RT

**Defensive Positions**:
- DE1, DE2, DT1, DT2
- MLB, OLB1, OLB2
- CB1, CB2, FS, SS

## 🎬 Camera System Usage

### Changing Camera Angles (Blueprint or C++)

```cpp
AFootballCameraManager* CameraManager = GetPlayerController()->PlayerCameraManager;
CameraManager->SetCameraAngle(ECameraAngle::Sideline);
```

### Triggering Replays

```cpp
CameraManager->StartReplay(5.f); // 5 second replay
```

### Available Camera Angles:
- `ECameraAngle::BehindQB`
- `ECameraAngle::Sideline`
- `ECameraAngle::EndZone`
- `ECameraAngle::Skycam`
- `ECameraAngle::BallFollow`
- `ECameraAngle::Replay`

## 🤖 Setting Up AI

### 1. Assign AI Controller to Characters

In Character Blueprint or Details Panel:
- AI Controller Class: `FootballAIController`

### 2. Create Behavior Tree (Optional)

If you want custom AI beyond the built-in pursuit:
1. Create Behavior Tree asset
2. Create Blackboard asset
3. Add BT tasks: `BTTask_FindBallCarrier`, `BTTask_RunRoute`
4. Assign BehaviorTree to `FootballAIController`

### 3. Route Types Available

- Go Route (straight deep)
- Slant (diagonal across middle)
- Out (toward sideline)
- In (toward middle)
- Post (deep diagonal toward center)
- Corner (deep diagonal toward sideline)
- Curl (deep then comeback)
- Flat (shallow across field)

## 🎨 Play Calling UI

### Creating Play Call Widget

1. **Create Widget Blueprint**:
   - Inherit from `PlayCallWidget`
   - Add 4 buttons (Play1Button, Play2Button, Play3Button, Play4Button)
   - Add PlayTitleText
   - Bind widgets using meta=(BindWidget)

2. **Show Play Call Menu**:
   ```cpp
   PlayCallWidget->ShowPlayCallMenu();
   ```

3. **Handle Play Selection** (Blueprint Event):
   - Implement `OnPlaySelected` event
   - Receives `FPlayData` with play information

## 🔧 Customization

### Tunable Parameters

**FootballCharacter**:
- `PassSpeed` (default: 2000.f) - Ball throw velocity
- `PassLeadTime` (default: 0.5s) - Lead time for receiver prediction
- `DefensePursuitSpeed` (default: 400.f) - How fast defense chases

**FootballBall**:
- `ProjectileGravityScale` (default: 0.5f) - Ball arc
- `MaxSpeed` (default: 3000.f) - Maximum ball velocity
- `HandSocketName` (default: "Hand_R") - Attachment socket

**FootballGameMode**:
- `LineOfScrimmage` (default: 0, 0, 100) - Ball spawn position
- `ResetDelay` (default: 0.75s) - Time before play reset

**FootballCameraManager**:
- `SidelineCameraHeight` (default: 500.f)
- `SidelineCameraDistance` (default: 1500.f)
- `SkycamHeight` (default: 2000.f)
- `BehindQBDistance` (default: 400.f)
- `CameraLerpSpeed` (default: 5.f) - Camera smoothing

## 📊 C++ Classes Reference

### Gameplay Core
- `AFootballGameMode` - Game state, scoring, play management
- `AFootballPlayerController` - Input handling
- `AFootballCharacter` - Player/AI character with team, position, animations
- `AFootballBall` - Projectile ball with catch mechanics
- `AFootballHUD` - On-screen score display

### Triggers
- `AFootballEndZoneTrigger` - Touchdown detection
- `AOutOfBoundsTrigger` - Sideline detection

### Animation
- `UFootballAnimInstance` - Animation blueprint base class

### Camera
- `AFootballCameraManager` - Multi-angle camera system with replays

### AI
- `AFootballAIController` - AI controller with perception
- `UBTTask_FindBallCarrier` - BT task to locate ball carrier
- `UBTTask_RunRoute` - BT task for receiver routes

### UI
- `UPlayCallWidget` - Play calling interface

### Data
- `UFormationData` - Formation data assets
- `FPlayData` - Play information struct
- `FPlayerFormationSlot` - Position data in formations

## 🧪 Testing Checklist

### Basic Gameplay
- [ ] Press Space → Ball snaps to QB
- [ ] Press 1-4 → Ball flies to receivers
- [ ] Ball caught automatically by receivers
- [ ] Defense pursues ball carrier
- [ ] Defensive overlap → Play ends
- [ ] End zone entry → Score increments
- [ ] Play resets after 0.75s

### Camera System
- [ ] Camera follows QB/ball carrier
- [ ] Can switch camera angles
- [ ] Replay triggers correctly
- [ ] Camera transitions are smooth

### AI System
- [ ] AI finds ball carrier
- [ ] AI runs routes (if BT configured)
- [ ] AI perception detects players

### UI System
- [ ] Play call menu displays
- [ ] Can select plays
- [ ] Play data loads correctly

### Out of Bounds
- [ ] Crossing sideline ends play
- [ ] Only when carrying ball

## 🎓 Animation Setup Guide

### 1. Create Animation Blueprint

1. Create Animation Blueprint (Content Browser)
2. Set Parent Class: `FootballAnimInstance`
3. Set Skeleton to your character's skeleton

### 2. Animation State Machine

Create states for:
- **Idle/Run** (use Speed variable)
- **Throwing** (use bIsThrowing)
- **Catching** (use bIsCatching)
- **Tackled** (use bIsTackled)

### 3. Assign to Character

- In Character Blueprint or C++
- Set Anim Class to your Animation Blueprint

## 📝 Module Dependencies

Updated in `Football7v7.Build.cs`:

```csharp
PublicDependencyModuleNames.AddRange(new string[] {
    "Core",
    "CoreUObject",
    "Engine",
    "InputCore",
    "AIModule",
    "GameplayTasks",
    "NavigationSystem",
    "UMG"
});

PrivateDependencyModuleNames.AddRange(new string[] {
    "Slate",
    "SlateCore"
});
```

## 🔄 Migration from 7v7 to 11v11

If you have existing 7v7 setups:

1. Legacy positions (OL, DL, LB, S1, S2, Rover) still work
2. Add new positions gradually (LT, LG, C, RG, RT for offense)
3. Use FormationData assets to organize 11v11 layouts
4. All existing code remains compatible

## 🤝 Contributing

This is a prototype/learning project. Feel free to:
- Add more formations
- Create additional routes
- Improve AI logic
- Add penalty systems
- Implement play clock
- Add multiplayer support

## 📄 License

[Specify your license]

## 🙏 Credits

Built with Unreal Engine 5 and C++.

## 📞 Support

For issues or questions, check the CLAUDE.md file for AI assistant guidelines or create an issue in the repository.

---

**Ready to play football!** 🏈
