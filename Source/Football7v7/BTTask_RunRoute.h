// BTTask_RunRoute.h
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_RunRoute.generated.h"

UENUM(BlueprintType)
enum class ERouteType : uint8
{
	Go          UMETA(DisplayName = "Go Route"),
	Slant       UMETA(DisplayName = "Slant"),
	Out         UMETA(DisplayName = "Out Route"),
	In          UMETA(DisplayName = "In Route"),
	Post        UMETA(DisplayName = "Post"),
	Corner      UMETA(DisplayName = "Corner"),
	Curl        UMETA(DisplayName = "Curl"),
	Flat        UMETA(DisplayName = "Flat")
};

UCLASS()
class FOOTBALL7V7_API UBTTask_RunRoute : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_RunRoute();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "AI")
	ERouteType RouteType;

	UPROPERTY(EditAnywhere, Category = "AI")
	float RouteDepth;

	UPROPERTY(EditAnywhere, Category = "AI")
	float RouteDuration;

protected:
	FVector CalculateRouteTarget(const FVector& StartLocation, const FRotator& StartRotation);
	float ElapsedTime;
};
