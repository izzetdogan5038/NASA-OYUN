// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MissionTypes.h"
#include "MissionPlayerController.generated.h"

UCLASS()
class NASAOYUN_API AMissionPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Mission|UI")
	TSubclassOf<class UMissionHUDWidget> HUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Mission|UI")
	TSubclassOf<class UMissionDesignerWidget> DesignerWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Mission|UI")
	TSubclassOf<class UMissionSimulationWidget> SimulationWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Mission|UI")
	TSubclassOf<class UMissionResultsWidget> ResultsWidgetClass;

	void RunDemoMission();

protected:
	UPROPERTY() class UMissionHUDWidget* HUDWidget = nullptr;
	UPROPERTY() class UMissionDesignerWidget* DesignerWidget = nullptr;
	UPROPERTY() class UMissionSimulationWidget* SimulationWidget = nullptr;
	UPROPERTY() class UMissionResultsWidget* ResultsWidget = nullptr;
};
