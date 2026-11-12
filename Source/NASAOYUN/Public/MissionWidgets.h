// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MissionTypes.h"
#include "MissionSimulationSubsystem.h"
#include "MissionWidgets.generated.h"

// Pure C++ HUD with Slate bars. Blueprint can extend for styling.
UCLASS(Blueprintable)
class NASAOYUN_API UMissionHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual TSharedRef<SWidget> RebuildWidget() override;

	UFUNCTION(BlueprintNativeEvent, Category = "Mission|UI")
	void UpdateResourceBars(const FResourceBudget& Budget);
	virtual void UpdateResourceBars_Implementation(const FResourceBudget& Budget);

protected:
	TSharedPtr<class STextBlock> MassText;
	TSharedPtr<class SProgressBar> MassBar;
	TSharedPtr<class STextBlock> PowerText;
	TSharedPtr<class SProgressBar> PowerBar;
	TSharedPtr<class STextBlock> BudgetText;
	TSharedPtr<class SProgressBar> BudgetBar;
	TSharedPtr<class STextBlock> DataText;
	TSharedPtr<class SProgressBar> DataBar;
	TSharedPtr<class STextBlock> CommsText;
	TSharedPtr<class SProgressBar> CommsBar;
	TSharedPtr<class STextBlock> LifeText;

	float MassCap = 2000.f;
	float BudgetCap = 8000.f;
};

UCLASS(Blueprintable)
class NASAOYUN_API UMissionDesignerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual TSharedRef<SWidget> RebuildWidget() override;

	UFUNCTION(BlueprintNativeEvent, Category = "Mission|UI")
	void RefreshResources(const FResourceBudget& Budget, const FValidationResult& Validation);
	virtual void RefreshResources_Implementation(const FResourceBudget& Budget, const FValidationResult& Validation);

protected:
	TSharedPtr<class STextBlock> StatusText;
	TSharedPtr<class SVerticalBox> ListContainer;
};

UCLASS(Blueprintable)
class NASAOYUN_API UMissionSimulationWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual TSharedRef<SWidget> RebuildWidget() override;

	UFUNCTION(BlueprintNativeEvent, Category = "Mission|UI")
	void PlaySimulation(const TArray<FSimEvent>& Events, float DurationSeconds);
	virtual void PlaySimulation_Implementation(const TArray<FSimEvent>& Events, float DurationSeconds);

protected:
	TSharedPtr<class SScrollBox> EventLog;
	TSharedPtr<class STextBlock> TimeText;
};

UCLASS(Blueprintable)
class NASAOYUN_API UMissionResultsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual TSharedRef<SWidget> RebuildWidget() override;

	UFUNCTION(BlueprintNativeEvent, Category = "Mission|UI")
	void ShowResults(const FMissionScore& Score, const TArray<FSimEvent>& Events);
	virtual void ShowResults_Implementation(const FMissionScore& Score, const TArray<FSimEvent>& Events);

protected:
	TSharedPtr<class STextBlock> GradeText;
	TSharedPtr<class STextBlock> TotalText;
	TSharedPtr<class STextBlock> DetailsText;
};
