// PlayCallWidget.cpp
#include "PlayCallWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UPlayCallWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Bind button clicks
	if (Play1Button)
	{
		Play1Button->OnClicked.AddDynamic(this, &UPlayCallWidget::OnPlay1Clicked);
	}
	if (Play2Button)
	{
		Play2Button->OnClicked.AddDynamic(this, &UPlayCallWidget::OnPlay2Clicked);
	}
	if (Play3Button)
	{
		Play3Button->OnClicked.AddDynamic(this, &UPlayCallWidget::OnPlay3Clicked);
	}
	if (Play4Button)
	{
		Play4Button->OnClicked.AddDynamic(this, &UPlayCallWidget::OnPlay4Clicked);
	}

	// Initialize with some default plays
	if (OffensivePlays.Num() == 0)
	{
		FPlayData Play1;
		Play1.PlayName = TEXT("Four Verticals");
		Play1.PlayDescription = TEXT("All receivers run deep routes");
		Play1.bIsRunPlay = false;
		OffensivePlays.Add(Play1);

		FPlayData Play2;
		Play2.PlayName = TEXT("Slants");
		Play2.PlayDescription = TEXT("Quick slant routes across the middle");
		Play2.bIsRunPlay = false;
		OffensivePlays.Add(Play2);

		FPlayData Play3;
		Play3.PlayName = TEXT("HB Draw");
		Play3.PlayDescription = TEXT("Running back delayed rush");
		Play3.bIsRunPlay = true;
		OffensivePlays.Add(Play3);

		FPlayData Play4;
		Play4.PlayName = TEXT("Corners");
		Play4.PlayDescription = TEXT("Corner routes to sidelines");
		Play4.bIsRunPlay = false;
		OffensivePlays.Add(Play4);
	}
}

void UPlayCallWidget::ShowPlayCallMenu()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UPlayCallWidget::HidePlayCallMenu()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UPlayCallWidget::SelectPlay(int32 PlayIndex)
{
	if (OffensivePlays.IsValidIndex(PlayIndex))
	{
		OnPlaySelected(OffensivePlays[PlayIndex]);
		HidePlayCallMenu();
	}
}

void UPlayCallWidget::OnPlay1Clicked()
{
	SelectPlay(0);
}

void UPlayCallWidget::OnPlay2Clicked()
{
	SelectPlay(1);
}

void UPlayCallWidget::OnPlay3Clicked()
{
	SelectPlay(2);
}

void UPlayCallWidget::OnPlay4Clicked()
{
	SelectPlay(3);
}
