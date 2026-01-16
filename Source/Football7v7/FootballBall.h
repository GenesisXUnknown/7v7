// FootballBall.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FootballBall.generated.h"

class AFootballCharacter;
class UStaticMeshComponent;
class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class FOOTBALL7V7_API AFootballBall : public AActor
{
    GENERATED_BODY()

public:
    AFootballBall();

    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable, Category = "Football")
    void ThrowBall(FVector Velocity);

    UFUNCTION(BlueprintCallable, Category = "Football")
    void AttachToCharacter(AFootballCharacter* Character);

    UFUNCTION(BlueprintCallable, Category = "Football")
    void ResetBall();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USphereComponent* CollisionComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* BallMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UProjectileMovementComponent* ProjectileMovement;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Football")
    FName HandSocketName;

    UFUNCTION()
    void OnBallOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                       bool bFromSweep, const FHitResult& SweepResult);
};
