// FootballAnimInstance.cpp
#include "FootballAnimInstance.h"
#include "FootballCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UFootballAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwningCharacter = Cast<AFootballCharacter>(TryGetPawnOwner());
}

void UFootballAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!OwningCharacter)
	{
		OwningCharacter = Cast<AFootballCharacter>(TryGetPawnOwner());
		if (!OwningCharacter) return;
	}

	// Get velocity and calculate speed
	FVector Velocity = OwningCharacter->GetVelocity();
	Speed = Velocity.Size2D();

	// Calculate direction relative to character rotation
	if (Speed > 0.f)
	{
		FRotator ActorRotation = OwningCharacter->GetActorRotation();
		FRotator VelocityRotation = Velocity.Rotation();
		Direction = UKismetMathLibrary::NormalizedDeltaRotator(VelocityRotation, ActorRotation).Yaw;
	}
	else
	{
		Direction = 0.f;
	}

	// Check if in air
	UCharacterMovementComponent* Movement = OwningCharacter->GetCharacterMovement();
	if (Movement)
	{
		bIsInAir = Movement->IsFalling();
	}

	// Get ball status
	bHasBall = OwningCharacter->HasBall();

	// Get animation states from character
	bIsThrowing = OwningCharacter->IsThrowingAnimation();
	bIsCatching = OwningCharacter->IsCatchingAnimation();
	bIsTackled = OwningCharacter->IsTackledAnimation();
}
