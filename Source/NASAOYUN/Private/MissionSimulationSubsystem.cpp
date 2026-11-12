// Copyright Epic Games, Inc. All Rights Reserved.

#include "MissionSimulationSubsystem.h"
#include "Kismet/KismetMathLibrary.h"

void UMissionSimulationSubsystem::RunSimulation(const FMissionDesign& Design, const FMissionRow& Mission, int32 MonthsToSimulate, const FResourceBudget& Budget)
{
	LastEvents.Empty();
	LastReliability = 1.f;
	LastDataCollectedGbit = 0.f;

	const int32 Months = FMath::Max(1, MonthsToSimulate);
	for (int32 m = 1; m <= Months; ++m)
	{
		TickMonth(m, Design, Mission, Budget);
	}

	// Data collected scales with lifetime vs required and comms capacity
	const float LifetimeFactor = FMath::Clamp((float)Budget.LifetimeMonths / FMath::Max(1, Mission.RequiredLifetimeMonths), 0.f, 1.5f);
	LastDataCollectedGbit = Budget.DataRateGbitDay * 30.f * (float)Months * LifetimeFactor;
}

void UMissionSimulationSubsystem::TickMonth(int32 Month, const FMissionDesign& /*Design*/, const FMissionRow& Mission, const FResourceBudget& Budget)
{
	// Roll for a random event each month (~15% chance)
	const float Roll = FMath::FRand();
	if (Roll < 0.15f)
	{
		FSimEvent E;
		E.EventId = (Roll < 0.05f) ? FName(TEXT("SolarStorm")) : (Roll < 0.10f ? FName(TEXT("SensorFault")) : FName(TEXT("CommDropout")));
		if (E.EventId == FName(TEXT("SolarStorm")))
		{
			E.Title = FText::FromString(TEXT("Solar Storm"));
			E.Description = FText::FromString(TEXT("Increased radiation reduces power output temporarily."));
			E.Severity = 0.6f;
			E.PowerDeltaW = -Budget.PowerGenW * 0.25f;
			E.ReliabilityHit = 0.05f;
		}
		else if (E.EventId == FName(TEXT("SensorFault")))
		{
			E.Title = FText::FromString(TEXT("Instrument Fault"));
			E.Description = FText::FromString(TEXT("An instrument reports degraded data."));
			E.Severity = 0.4f;
			E.DataLossGbit = Budget.DataRateGbitDay * 2.f;
			E.ReliabilityHit = 0.03f;
		}
		else
		{
			E.Title = FText::FromString(TEXT("Communications Dropout"));
			E.Description = FText::FromString(TEXT("Temporary loss of downlink window."));
			E.Severity = 0.3f;
			E.DataLossGbit = Budget.DataRateGbitDay * 1.f;
		}
		LastEvents.Add(E);
		LastReliability = FMath::Clamp(LastReliability - E.ReliabilityHit, 0.f, 1.f);
	}

	// Power margin check: if generation < draw, reliability degrades
	if (Budget.PowerGenW < Budget.PowerDrawW)
	{
		LastReliability = FMath::Clamp(LastReliability - 0.02f, 0.f, 1.f);
	}
}
