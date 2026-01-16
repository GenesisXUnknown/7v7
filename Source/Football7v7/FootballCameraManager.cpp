// FootballCameraManager.cpp
#include "FootballCameraManager.h"
#include "FootballCharacter.h"
#include "FootballGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AFootballCameraManager::AFootballCameraManager()
{
	CurrentCameraAngle = ECameraAngle::BehindQB;
	SidelineCameraHeight = 500.f;
	SidelineCameraDistance = 1500.f;
	SkycamHeight = 2000.f;
	BehindQBDistance = 400.f;
	BehindQBHeight = 200.f;
	CameraLerpSpeed = 5.f;
	bIsInReplay = false;
	ReplayTimeRemaining = 0.f;
}

void AFootballCameraManager::UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime)
{
	Super::UpdateViewTarget(OutVT, DeltaTime);

	if (bIsInReplay)
	{
		ReplayTimeRemaining -= DeltaTime;
		if (ReplayTimeRemaining <= 0.f)
		{
			StopReplay();
		}
	}

	UpdateTrackedPlayer();

	FVector TargetLocation = CalculateCameraLocation(DeltaTime);
	FRotator TargetRotation = CalculateCameraRotation(DeltaTime);

	// Smooth interpolation
	FVector CurrentLocation = GetCameraLocation();
	FRotator CurrentRotation = GetCameraRotation();

	FVector NewLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, DeltaTime, CameraLerpSpeed);
	FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, CameraLerpSpeed);

	OutVT.POV.Location = NewLocation;
	OutVT.POV.Rotation = NewRotation;
}

void AFootballCameraManager::SetCameraAngle(ECameraAngle NewAngle)
{
	CurrentCameraAngle = NewAngle;
}

void AFootballCameraManager::StartReplay(float ReplayDuration)
{
	bIsInReplay = true;
	ReplayTimeRemaining = ReplayDuration;
	CurrentCameraAngle = ECameraAngle::Replay;
}

void AFootballCameraManager::StopReplay()
{
	bIsInReplay = false;
	ReplayTimeRemaining = 0.f;
	CurrentCameraAngle = ECameraAngle::BehindQB;
}

void AFootballCameraManager::UpdateTrackedPlayer()
{
	// Find ball carrier or QB
	TArray<AActor*> FoundCharacters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFootballCharacter::StaticClass(), FoundCharacters);

	for (AActor* Actor : FoundCharacters)
	{
		AFootballCharacter* Character = Cast<AFootballCharacter>(Actor);
		if (Character && Character->HasBall())
		{
			TrackedPlayer = Character;
			return;
		}
	}

	// Default to QB if no ball carrier
	for (AActor* Actor : FoundCharacters)
	{
		AFootballCharacter* Character = Cast<AFootballCharacter>(Actor);
		if (Character && Character->GetPosition() == EPosition::QB)
		{
			TrackedPlayer = Character;
			return;
		}
	}
}

FVector AFootballCameraManager::CalculateCameraLocation(float DeltaTime)
{
	if (!TrackedPlayer)
	{
		return GetCameraLocation();
	}

	FVector PlayerLocation = TrackedPlayer->GetActorLocation();
	FRotator PlayerRotation = TrackedPlayer->GetActorRotation();

	switch (CurrentCameraAngle)
	{
		case ECameraAngle::BehindQB:
		{
			FVector Offset = PlayerRotation.Vector() * -BehindQBDistance;
			Offset.Z = BehindQBHeight;
			return PlayerLocation + Offset;
		}

		case ECameraAngle::Sideline:
		{
			FVector SidelineOffset = FVector(0.f, SidelineCameraDistance, SidelineCameraHeight);
			return PlayerLocation + SidelineOffset;
		}

		case ECameraAngle::EndZone:
		{
			FVector EndZoneOffset = FVector(-1500.f, 0.f, 600.f);
			return PlayerLocation + EndZoneOffset;
		}

		case ECameraAngle::Skycam:
		{
			return FVector(PlayerLocation.X, PlayerLocation.Y, PlayerLocation.Z + SkycamHeight);
		}

		case ECameraAngle::BallFollow:
		case ECameraAngle::Replay:
		{
			FVector Offset = FVector(-300.f, 200.f, 150.f);
			return PlayerLocation + Offset;
		}

		default:
			return GetCameraLocation();
	}
}

FRotator AFootballCameraManager::CalculateCameraRotation(float DeltaTime)
{
	if (!TrackedPlayer)
	{
		return GetCameraRotation();
	}

	FVector CameraLocation = CalculateCameraLocation(DeltaTime);
	FVector PlayerLocation = TrackedPlayer->GetActorLocation();

	return UKismetMathLibrary::FindLookAtRotation(CameraLocation, PlayerLocation);
}
