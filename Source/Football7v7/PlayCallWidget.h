// PlayCallWidget.h
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FootballTypes.h"
#include "PlayCallWidget.generated.h"

class UButton;
class UTextBlock;
class UImage;

USTRUCT(BlueprintType)
struct FPlayData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PlayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PlayDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* PlayDiagram;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> ReceiverRoutes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsRunPlay;
};

UCLASS()
class FOOTBALL7V7_API UPlayCallWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "PlayCall")
	void ShowPlayCallMenu();

	UFUNCTION(BlueprintCallable, Category = "PlayCall")
	void HidePlayCallMenu();

	UFUNCTION(BlueprintCallable, Category = "PlayCall")
	void SelectPlay(int32 PlayIndex);

	UFUNCTION(BlueprintImplementableEvent, Category = "PlayCall")
	void OnPlaySelected(const FPlayData& SelectedPlay);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayCall")
	TArray<FPlayData> OffensivePlays;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayCall")
	TArray<FPlayData> DefensivePlays;

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* Play1Button;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* Play2Button;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* Play3Button;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* Play4Button;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* PlayTitleText;

private:
	UFUNCTION()
	void OnPlay1Clicked();

	UFUNCTION()
	void OnPlay2Clicked();

	UFUNCTION()
	void OnPlay3Clicked();

	UFUNCTION()
	void OnPlay4Clicked();
};
