// BTTask_FindBallCarrier.cpp
#include "BTTask_FindBallCarrier.h"
#include "FootballCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"

UBTTask_FindBallCarrier::UBTTask_FindBallCarrier()
{
	NodeName = "Find Ball Carrier";
	SearchRadius = 5000.f;
}

EBTNodeResult::Type UBTTask_FindBallCarrier::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}

	APawn* AIPawn = AIController->GetPawn();
	if (!AIPawn)
	{
		return EBTNodeResult::Failed;
	}

	// Find all characters
	TArray<AActor*> FoundCharacters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFootballCharacter::StaticClass(), FoundCharacters);

	AFootballCharacter* BallCarrier = nullptr;
	float ClosestDistance = SearchRadius;

	// Find ball carrier
	for (AActor* Actor : FoundCharacters)
	{
		AFootballCharacter* Character = Cast<AFootballCharacter>(Actor);
		if (Character && Character->HasBall())
		{
			float Distance = FVector::Dist(AIPawn->GetActorLocation(), Character->GetActorLocation());
			if (Distance < ClosestDistance)
			{
				BallCarrier = Character;
				ClosestDistance = Distance;
			}
		}
	}

	if (BallCarrier)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(BallCarrierKey.SelectedKeyName, BallCarrier);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
