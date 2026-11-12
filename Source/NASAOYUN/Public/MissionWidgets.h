// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MissionTypes.h"
#include "MissionSimulationSubsystem.h"
#include "MissionWidgets.generated.h"

UCLASS(Abstract, Blueprintable)
class NASAOYUN_API UMissionDesignerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Mission|UI")
	void RefreshResources(const FResourceBudget& Budget, const FValidationResult& Validation);
};

UCLASS(Abstract, Blueprintable)
class NASAOYUN_API UMissionHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Mission|UI")
	void UpdateResourceBars(const FResourceBudget& Budget);
};

UCLASS(Abstract, Blueprintable)
class NASAOYUN_API UMissionSimulationWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Mission|UI")
	void PlaySimulation(const TArray<FSimEvent>& Events, float DurationSeconds);
};

UCLASS(Abstract, Blueprintable)
class NASAOYUN_API UMissionResultsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Mission|UI")
	void ShowResults(const FMissionScore& Score, const TArray<FSimEvent>& Events);
};
