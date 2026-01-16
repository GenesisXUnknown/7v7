// FormationData.h
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FootballTypes.h"
#include "FormationData.generated.h"

USTRUCT(BlueprintType)
struct FPlayerFormationSlot
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPosition Position;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector RelativeLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator RelativeRotation;

	FPlayerFormationSlot()
		: Position(EPosition::None)
		, RelativeLocation(FVector::ZeroVector)
		, RelativeRotation(FRotator::ZeroRotator)
	{}
};

UCLASS(BlueprintType)
class FOOTBALL7V7_API UFormationData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Formation")
	FString FormationName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Formation")
	ETeam Team;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Formation")
	bool bIs11v11;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Formation")
	TArray<FPlayerFormationSlot> PlayerSlots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Formation")
	FString Description;

	// Helper functions
	UFUNCTION(BlueprintCallable, Category = "Formation")
	static UFormationData* CreateProFormation();

	UFUNCTION(BlueprintCallable, Category = "Formation")
	static UFormationData* CreateShotgunFormation();

	UFUNCTION(BlueprintCallable, Category = "Formation")
	static UFormationData* Create43DefenseFormation();

	UFUNCTION(BlueprintCallable, Category = "Formation")
	static UFormationData* Create34DefenseFormation();
};
