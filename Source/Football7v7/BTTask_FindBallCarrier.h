// BTTask_FindBallCarrier.h
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindBallCarrier.generated.h"

UCLASS()
class FOOTBALL7V7_API UBTTask_FindBallCarrier : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_FindBallCarrier();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector BallCarrierKey;

	UPROPERTY(EditAnywhere, Category = "AI")
	float SearchRadius;
};
