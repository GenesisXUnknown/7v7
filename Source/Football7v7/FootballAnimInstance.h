// FootballAnimInstance.h
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "FootballAnimInstance.generated.h"

class AFootballCharacter;

UCLASS()
class FOOTBALL7V7_API UFootballAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeInitializeAnimation() override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	AFootballCharacter* OwningCharacter;

	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	float Speed;

	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	float Direction;

	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	bool bIsInAir;

	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	bool bHasBall;

	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	bool bIsThrowing;

	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	bool bIsCatching;

	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	bool bIsTackled;
};
