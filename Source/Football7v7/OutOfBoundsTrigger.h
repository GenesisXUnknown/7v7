// OutOfBoundsTrigger.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OutOfBoundsTrigger.generated.h"

class UBoxComponent;

UCLASS()
class FOOTBALL7V7_API AOutOfBoundsTrigger : public AActor
{
	GENERATED_BODY()

public:
	AOutOfBoundsTrigger();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* BoundaryVolume;

	UFUNCTION()
	void OnBoundaryOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	                       bool bFromSweep, const FHitResult& SweepResult);
};
