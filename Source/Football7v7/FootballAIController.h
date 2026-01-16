// FootballAIController.h
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FootballAIController.generated.h"

class UBehaviorTree;
class UBlackboardComponent;

UCLASS()
class FOOTBALL7V7_API AFootballAIController : public AAIController
{
	GENERATED_BODY()

public:
	AFootballAIController();

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTree;

protected:
	virtual void BeginPlay() override;
};
