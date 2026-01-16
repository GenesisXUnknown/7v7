// FootballAIController.cpp
#include "FootballAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AFootballAIController::AFootballAIController()
{
	BehaviorTree = nullptr;

	// Setup blackboard and perception
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent")));

	// Configure sight sense
	UAISenseConfig_Sight* SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	if (SightConfig)
	{
		SightConfig->SightRadius = 3000.f;
		SightConfig->LoseSightRadius = 3500.f;
		SightConfig->PeripheralVisionAngleDegrees = 90.f;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

		GetPerceptionComponent()->ConfigureSense(*SightConfig);
		GetPerceptionComponent()->SetDominantSense(SightConfig->GetSenseImplementation());
	}
}

void AFootballAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AFootballAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
	}
}

void AFootballAIController::OnUnPossess()
{
	Super::OnUnPossess();

	if (UBehaviorTreeComponent* BTComp = Cast<UBehaviorTreeComponent>(GetBrainComponent()))
	{
		BTComp->StopTree();
	}
}
