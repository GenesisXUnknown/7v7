// BTTask_RunRoute.cpp
#include "BTTask_RunRoute.h"
#include "FootballCharacter.h"
#include "AIController.h"
#include "NavigationSystem.h"

UBTTask_RunRoute::UBTTask_RunRoute()
{
	NodeName = "Run Route";
	RouteType = ERouteType::Go;
	RouteDepth = 1000.f;
	RouteDuration = 3.f;
	ElapsedTime = 0.f;
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_RunRoute::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	FVector StartLocation = AIPawn->GetActorLocation();
	FRotator StartRotation = AIPawn->GetActorRotation();

	FVector TargetLocation = CalculateRouteTarget(StartLocation, StartRotation);

	// Move to target
	AIController->MoveToLocation(TargetLocation, 5.f, true, true, false, true);

	ElapsedTime = 0.f;
	return EBTNodeResult::InProgress;
}

void UBTTask_RunRoute::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ElapsedTime += DeltaSeconds;

	if (ElapsedTime >= RouteDuration)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

FVector UBTTask_RunRoute::CalculateRouteTarget(const FVector& StartLocation, const FRotator& StartRotation)
{
	FVector Forward = StartRotation.Vector();
	FVector Right = FRotationMatrix(StartRotation).GetUnitAxis(EAxis::Y);

	switch (RouteType)
	{
		case ERouteType::Go:
			return StartLocation + (Forward * RouteDepth);

		case ERouteType::Slant:
			return StartLocation + (Forward * RouteDepth * 0.7f) + (Right * RouteDepth * 0.3f);

		case ERouteType::Out:
			return StartLocation + (Forward * RouteDepth * 0.5f) + (Right * RouteDepth * 0.5f);

		case ERouteType::In:
			return StartLocation + (Forward * RouteDepth * 0.5f) + (Right * RouteDepth * -0.5f);

		case ERouteType::Post:
			return StartLocation + (Forward * RouteDepth * 0.8f) + (Right * RouteDepth * -0.2f);

		case ERouteType::Corner:
			return StartLocation + (Forward * RouteDepth * 0.6f) + (Right * RouteDepth * 0.4f);

		case ERouteType::Curl:
		{
			FVector Target = StartLocation + (Forward * RouteDepth);
			Target += (Forward * -RouteDepth * 0.2f); // Come back slightly
			return Target;
		}

		case ERouteType::Flat:
			return StartLocation + (Right * RouteDepth * 0.8f) + (Forward * RouteDepth * 0.2f);

		default:
			return StartLocation + (Forward * RouteDepth);
	}
}
