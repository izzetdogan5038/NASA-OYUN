// Copyright Epic Games, Inc. All Rights Reserved.

#include "MissionWidgets.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Progress/SProgressBar.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Styling/CoreStyle.h"

// ---------- HUD ----------
TSharedRef<SWidget> UMissionHUDWidget::RebuildWidget()
{
	return SNew(SVerticalBox)
		+ SVerticalBox::Slot().AutoHeight().Padding(4)
		[
			SNew(STextBlock).Text(FText::FromString(TEXT("MISSION HUD"))).Font(FCoreStyle::GetDefaultFontStyle("Bold", 14))
		]
		+ SVerticalBox::Slot().AutoHeight().Padding(4)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(4)
			[ SNew(STextBlock).Text(FText::FromString(TEXT("Mass"))) ]
			+ SHorizontalBox::Slot().FillWidth(1).Padding(4)
			[ SAssignNew(MassBar, SProgressBar).Percent(0.f) ]
			+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(4)
			[ SAssignNew(MassText, STextBlock).Text(FText::FromString(TEXT("0 / 0 kg"))) ]
		]
		+ SVerticalBox::Slot().AutoHeight().Padding(4)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(4)
			[ SNew(STextBlock).Text(FText::FromString(TEXT("Power"))) ]
			+ SHorizontalBox::Slot().FillWidth(1).Padding(4)
			[ SAssignNew(PowerBar, SProgressBar).Percent(0.f) ]
			+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(4)
			[ SAssignNew(PowerText, STextBlock).Text(FText::FromString(TEXT("0 / 0 W"))) ]
		]
		+ SVerticalBox::Slot().AutoHeight().Padding(4)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(4)
			[ SNew(STextBlock).Text(FText::FromString(TEXT("Budget"))) ]
			+ SHorizontalBox::Slot().FillWidth(1).Padding(4)
			[ SAssignNew(BudgetBar, SProgressBar).Percent(0.f) ]
			+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(4)
			[ SAssignNew(BudgetText, STextBlock).Text(FText::FromString(TEXT("0 / 0 kUSD"))) ]
		]
		+ SVerticalBox::Slot().AutoHeight().Padding(4)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(4)
			[ SNew(STextBlock).Text(FText::FromString(TEXT("Data"))) ]
			+ SHorizontalBox::Slot().FillWidth(1).Padding(4)
			[ SAssignNew(DataBar, SProgressBar).Percent(0.f) ]
			+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(4)
			[ SAssignNew(DataText, STextBlock).Text(FText::FromString(TEXT("0 / 0 Gbit/d"))) ]
		]
		+ SVerticalBox::Slot().AutoHeight().Padding(4)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(4)
			[ SNew(STextBlock).Text(FText::FromString(TEXT("Comms"))) ]
			+ SHorizontalBox::Slot().FillWidth(1).Padding(4)
			[ SAssignNew(CommsBar, SProgressBar).Percent(0.f) ]
			+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(4)
			[ SAssignNew(CommsText, STextBlock).Text(FText::FromString(TEXT("0 Gbit/d"))) ]
		]
		+ SVerticalBox::Slot().AutoHeight().Padding(4)
		[
			SAssignNew(LifeText, STextBlock).Text(FText::FromString(TEXT("Lifetime: 0 months")))
		];
}

void UMissionHUDWidget::UpdateResourceBars_Implementation(const FResourceBudget& Budget)
{
	if (MassBar.IsValid())
	{
		const float Pct = FMath::Clamp(Budget.MassKg / FMath::Max(1.f, MassCap), 0.f, 1.f);
		MassBar->SetPercent(Pct);
	}
	if (MassText.IsValid()) MassText->SetText(FText::FromString(FString::Printf(TEXT("%.1f kg"), Budget.MassKg)));
	if (PowerBar.IsValid())
	{
		const float Pct = FMath::Clamp(Budget.PowerDrawW / FMath::Max(1.f, Budget.PowerGenW), 0.f, 1.f);
		PowerBar->SetPercent(Pct);
	}
	if (PowerText.IsValid()) PowerText->SetText(FText::FromString(FString::Printf(TEXT("%.0f / %.0f W"), Budget.PowerDrawW, Budget.PowerGenW)));
	if (BudgetBar.IsValid())
	{
		const float Pct = FMath::Clamp(Budget.CostKUSD / FMath::Max(1.f, BudgetCap), 0.f, 1.f);
		BudgetBar->SetPercent(Pct);
	}
	if (BudgetText.IsValid()) BudgetText->SetText(FText::FromString(FString::Printf(TEXT("%.0f / %.0f kUSD"), Budget.CostKUSD, BudgetCap)));
	if (DataBar.IsValid())
	{
		const float Pct = FMath::Clamp(Budget.DataRateGbitDay / FMath::Max(0.01f, Budget.CommsCapacityGbitDay), 0.f, 1.f);
		DataBar->SetPercent(Pct);
	}
	if (DataText.IsValid()) DataText->SetText(FText::FromString(FString::Printf(TEXT("%.2f / %.2f Gbit/d"), Budget.DataRateGbitDay, Budget.CommsCapacityGbitDay)));
	if (CommsText.IsValid()) CommsText->SetText(FText::FromString(FString::Printf(TEXT("Comms cap: %.2f Gbit/d"), Budget.CommsCapacityGbitDay)));
	if (LifeText.IsValid()) LifeText->SetText(FText::FromString(FString::Printf(TEXT("Lifetime: %d months"), Budget.LifetimeMonths)));
}

// ---------- Designer ----------
TSharedRef<SWidget> UMissionDesignerWidget::RebuildWidget()
{
	return SNew(SVerticalBox)
		+ SVerticalBox::Slot().AutoHeight().Padding(4)
		[ SNew(STextBlock).Text(FText::FromString(TEXT("MISSION DESIGNER"))) ]
		+ SVerticalBox::Slot().FillHeight(1).Padding(4)
		[ SAssignNew(ListContainer, SVerticalBox) ]
		+ SVerticalBox::Slot().AutoHeight().Padding(4)
		[ SAssignNew(StatusText, STextBlock).Text(FText::FromString(TEXT("Select components, then Run Simulation."))) ];
}

void UMissionDesignerWidget::RefreshResources_Implementation(const FResourceBudget& Budget, const FValidationResult& Validation)
{
	if (StatusText.IsValid())
	{
		FString Msg = Validation.IsFullyValid() ? TEXT("Design VALID - ready to simulate.") : TEXT("Design INVALID:");
		if (!Validation.IsFullyValid())
		{
			for (const FText& M : Validation.Messages) { Msg += TEXT(" ") + M.ToString(); }
		}
		Msg += FString::Printf(TEXT(" | Mass %.1f  Power %.0f/%.0f  Budget %.0f  Data %.2f/%.2f  Life %d"),
			Budget.MassKg, Budget.PowerDrawW, Budget.PowerGenW, Budget.CostKUSD, Budget.DataRateGbitDay, Budget.CommsCapacityGbitDay, Budget.LifetimeMonths);
		StatusText->SetText(FText::FromString(Msg));
	}
}

// ---------- Simulation ----------
TSharedRef<SWidget> UMissionSimulationWidget::RebuildWidget()
{
	return SNew(SVerticalBox)
		+ SVerticalBox::Slot().AutoHeight().Padding(4)
		[ SAssignNew(TimeText, STextBlock).Text(FText::FromString(TEXT("Simulation: 0 / 0 months"))) ]
		+ SVerticalBox::Slot().FillHeight(1).Padding(4)
		[ SAssignNew(EventLog, SScrollBox) ];
}

void UMissionSimulationWidget::PlaySimulation_Implementation(const TArray<FSimEvent>& Events, float DurationSeconds)
{
	if (EventLog.IsValid())
	{
		EventLog->ClearChildren();
		for (const FSimEvent& E : Events)
		{
			EventLog->AddSlot()
			[
				SNew(STextBlock).Text(FText::Format(
					FText::FromString(TEXT("[{0}] {1}: {2}")),
					FText::AsNumber(0), E.Title, E.Description))
			];
		}
		if (Events.Num() == 0)
		{
			EventLog->AddSlot()[ SNew(STextBlock).Text(FText::FromString(TEXT("No events. Smooth mission."))) ];
		}
	}
	if (TimeText.IsValid())
	{
		TimeText->SetText(FText::FromString(FString::Printf(TEXT("Simulation complete. %d events. Duration %.1fs"), Events.Num(), DurationSeconds)));
	}
}

// ---------- Results ----------
TSharedRef<SWidget> UMissionResultsWidget::RebuildWidget()
{
	return SNew(SVerticalBox)
		+ SVerticalBox::Slot().AutoHeight().Padding(8)
		[ SAssignNew(GradeText, STextBlock).Text(FText::FromString(TEXT("Grade: -"))).Font(FCoreStyle::GetDefaultFontStyle("Bold", 20)) ]
		+ SVerticalBox::Slot().AutoHeight().Padding(4)
		[ SAssignNew(TotalText, STextBlock).Text(FText::FromString(TEXT("Total: 0"))) ]
		+ SVerticalBox::Slot().FillHeight(1).Padding(4)
		[ SAssignNew(DetailsText, STextBlock).Text(FText::FromString(TEXT(""))) ];
}

void UMissionResultsWidget::ShowResults_Implementation(const FMissionScore& Score, const TArray<FSimEvent>& Events)
{
	if (GradeText.IsValid()) GradeText->SetText(FText::Format(FText::FromString(TEXT("Grade: {0}")), Score.Grade));
	if (TotalText.IsValid()) TotalText->SetText(FText::FromString(FString::Printf(TEXT("Total: %.1f  (Science %.1f | Efficiency %.1f | Reliability %.1f | Collab %.1f)"),
		Score.TotalScore, Score.ScienceScore, Score.EfficiencyScore, Score.ReliabilityScore, Score.CollaborationScore)));
	if (DetailsText.IsValid())
	{
		FString D = FString::Printf(TEXT("Events: %d\n"), Events.Num());
		for (const FSimEvent& E : Events) { D += FString::Printf(TEXT("- %s: %s\n"), *E.Title.ToString(), *E.Description.ToString()); }
		DetailsText->SetText(FText::FromString(D));
	}
}
