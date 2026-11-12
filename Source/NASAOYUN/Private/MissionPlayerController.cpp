// Copyright Epic Games, Inc. All Rights Reserved.

#include "MissionPlayerController.h"
#include "MissionWidgets.h"
#include "MissionSimulationSubsystem.h"
#include "MissionScoringLibrary.h"
#include "MissionResourceManager.h"
#include "Kismet/GameplayStatics.h"

void AMissionPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!IsLocalController()) return;


	UClass* HUDClass = HUDWidgetClass ? HUDWidgetClass.Get() : UMissionHUDWidget::StaticClass(); HUDWidget = CreateWidget<UMissionHUDWidget>(this, HUDClass);
	if (HUDWidget) HUDWidget->AddToViewport(0);

	UClass* DesignerClass = DesignerWidgetClass ? DesignerWidgetClass.Get() : UMissionDesignerWidget::StaticClass(); DesignerWidget = CreateWidget<UMissionDesignerWidget>(this, DesignerClass);
	if (DesignerWidget) DesignerWidget->AddToViewport(1);

	UClass* SimClass = SimulationWidgetClass ? SimulationWidgetClass.Get() : UMissionSimulationWidget::StaticClass(); SimulationWidget = CreateWidget<UMissionSimulationWidget>(this, SimClass);
	if (SimulationWidget) SimulationWidget->AddToViewport(2);

	UClass* ResClass = ResultsWidgetClass ? ResultsWidgetClass.Get() : UMissionResultsWidget::StaticClass(); ResultsWidget = CreateWidget<UMissionResultsWidget>(this, ResClass);
	if (ResultsWidget) ResultsWidget->AddToViewport(3);

	RunDemoMission();
}

void AMissionPlayerController::RunDemoMission()
{
	// Hardcoded demo: Mars Water Scout mission design
	FMissionDesign Design;
	Design.MissionId = FName(TEXT("MarsWater"));
	Design.LaunchVehicleId = FName(TEXT("Falcon9"));
	Design.OrbitId = FName(TEXT("HEO_Molniya"));
	Design.BusComponentIds = { FName(TEXT("Struct_Al6061")), FName(TEXT("SolarPanel_Large")), FName(TEXT("Battery_LiIon")), FName(TEXT("Comms_XBand")), FName(TEXT("ADCS_Reaction")), FName(TEXT("OBC_Flight")), FName(TEXT("Thermal_Basic")) };
	Design.InstrumentIds = { FName(TEXT("Camera_HiRes")), FName(TEXT("Spectrometer")), FName(TEXT("Radar_SAR")) };

	FMissionRow Mission;
	Mission.MissionId = FName(TEXT("MarsWater"));
	Mission.DisplayName = FText::FromString(TEXT("Mars Water Scout"));
	Mission.BudgetKUSD = 8000.f;
	Mission.MassCapKg = 1500.f;
	Mission.MinScienceValue = 60.f;
	Mission.RequiredLifetimeMonths = 24;
	Mission.ObjectiveTags = { FName(TEXT("MarsWater")) };

	// Approximate resource budget (mirrors CSV data)
	FResourceBudget Budget;
	Budget.MassKg = 15.f + 9.f + 4.f + 5.5f + 3.5f + 2.f + 2.5f + 4.5f + 6.2f + 12.f;
	Budget.PowerGenW = 400.f;
	Budget.PowerDrawW = 0.f + 0.f + 0.f + 25.f + 15.f + 8.f + 0.f + 12.f + 18.f + 40.f;
	Budget.CostKUSD = 20.f + 90.f + 25.f + 70.f + 40.f + 30.f + 12.f + 45.f + 80.f + 150.f;
	Budget.DataRateGbitDay = 2.5f + 4.0f + 8.0f;
	Budget.CommsCapacityGbitDay = 20.f;
	Budget.LifetimeMonths = 84;

	FValidationResult Validation = UMissionResourceManager::Validate(Design, Mission, Budget, 22800.f / 2.0f);

	float ScienceSum = 35.f + 50.f + 60.f;

	// Simulation
	UMissionSimulationSubsystem* Sim = GetGameInstance() ? GetGameInstance()->GetSubsystem<UMissionSimulationSubsystem>() : nullptr;
	if (Sim)
	{
		Sim->RunSimulation(Design, Mission, 24, Budget);
	}

	FMissionScore Score = UMissionScoringLibrary::ComputeScore(Mission, Design, Budget, Validation,
		Sim ? Sim->LastReliability : 1.f,
		Sim ? Sim->LastDataCollectedGbit : 0.f,
		Design.InstrumentIds.Num(),
		ScienceSum);

	// Drive UI
	if (HUDWidget) HUDWidget->UpdateResourceBars(Budget);
	if (DesignerWidget) DesignerWidget->RefreshResources(Budget, Validation);
	if (SimulationWidget && Sim) SimulationWidget->PlaySimulation(Sim->LastEvents, 2.f);
	if (ResultsWidget) ResultsWidget->ShowResults(Score, Sim ? Sim->LastEvents : TArray<FSimEvent>());
}


