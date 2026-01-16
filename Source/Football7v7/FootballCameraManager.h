// FootballCameraManager.h
#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "FootballCameraManager.generated.h"

class ACameraActor;
class AFootballCharacter;

UENUM(BlueprintType)
enum class ECameraAngle : uint8
{
	BehindQB        UMETA(DisplayName = "Behind QB"),
	Sideline        UMETA(DisplayName = "Sideline"),
	EndZone         UMETA(DisplayName = "End Zone"),
	Skycam          UMETA(DisplayName = "Skycam"),
	BallFollow      UMETA(DisplayName = "Ball Follow"),
	Replay          UMETA(DisplayName = "Replay")
};

UCLASS()
class FOOTBALL7V7_API AFootballCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

public:
	AFootballCameraManager();

	virtual void UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Camera")
	void SetCameraAngle(ECameraAngle NewAngle);

	UFUNCTION(BlueprintCallable, Category = "Camera")
	void StartReplay(float ReplayDuration = 5.f);

	UFUNCTION(BlueprintCallable, Category = "Camera")
	void StopReplay();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	ECameraAngle CurrentCameraAngle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float SidelineCameraHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float SidelineCameraDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float SkycamHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float BehindQBDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float BehindQBHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float CameraLerpSpeed;

protected:
	UPROPERTY()
	bool bIsInReplay;

	UPROPERTY()
	float ReplayTimeRemaining;

	UPROPERTY()
	AFootballCharacter* TrackedPlayer;

	FVector CalculateCameraLocation(float DeltaTime);
	FRotator CalculateCameraRotation(float DeltaTime);
	void UpdateTrackedPlayer();
};
