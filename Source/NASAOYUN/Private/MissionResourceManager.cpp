// Copyright Epic Games, Inc. All Rights Reserved.

#include "MissionResourceManager.h"

FResourceBudget UMissionResourceManager::ComputeBudget(
	const FMissionDesign& Design,
	UDataTable* InstrumentTable,
	UDataTable* BusTable,
	UDataTable* /*LaunchTable*/,
	UDataTable* OrbitTable)
{
	FResourceBudget Budget;

	// Bus components
	if (BusTable)
	{
		for (const FName& Id : Design.BusComponentIds)
		{
			if (const FBusComponentRow* Row = BusTable->FindRow<FBusComponentRow>(Id, TEXT("ComputeBudget")))
			{
				Budget.MassKg += Row->MassKg;
				Budget.PowerGenW += Row->PowerGenW;
				Budget.PowerDrawW += Row->PowerDrawW;
				Budget.CostKUSD += Row->CostKUSD;
				Budget.DataRateGbitDay += 0.f;
				Budget.CommsCapacityGbitDay += Row->DataCapacityGbitDay;
			}
		}
	}

	// Instruments
	if (InstrumentTable)
	{
		for (const FName& Id : Design.InstrumentIds)
		{
			if (const FInstrumentRow* Row = InstrumentTable->FindRow<FInstrumentRow>(Id, TEXT("ComputeBudget")))
			{
				Budget.MassKg += Row->MassKg;
				Budget.PowerDrawW += Row->PowerDrawW;
				Budget.CostKUSD += Row->CostKUSD;
				Budget.DataRateGbitDay += Row->DataRateGbitDay;
			}
		}
	}

	// Orbit lifetime
	if (OrbitTable)
	{
		if (const FOrbitRow* Row = OrbitTable->FindRow<FOrbitRow>(Design.OrbitId, TEXT("ComputeBudget")))
		{
			Budget.LifetimeMonths = Row->ExpectedLifetimeMonths;
		}
	}

	return Budget;
}

FValidationResult UMissionResourceManager::Validate(
	const FMissionDesign& Design,
	const FMissionRow& Mission,
	const FResourceBudget& Budget,
	float LaunchCapacityKg)
{
	FValidationResult R;

	// Mass check
	R.bMassOK = Budget.MassKg <= LaunchCapacityKg && Budget.MassKg <= Mission.MassCapKg;
	if (!R.bMassOK)
		R.Messages.Add(FText::FromString(FString::Printf(TEXT("Mass %.1f kg exceeds capacity %.1f kg"), Budget.MassKg, LaunchCapacityKg)));

	// Power check (generation >= draw with 20% margin)
	const float Required = Budget.PowerDrawW * 1.2f;
	R.bPowerOK = Budget.PowerGenW >= Required;
	if (!R.bPowerOK)
		R.Messages.Add(FText::FromString(FString::Printf(TEXT("Power: gen %.1f W < required %.1f W (draw %.1f + 20%%)"), Budget.PowerGenW, Required, Budget.PowerDrawW)));

	// Budget check
	R.bBudgetOK = Budget.CostKUSD <= Mission.BudgetKUSD;
	if (!R.bBudgetOK)
		R.Messages.Add(FText::FromString(FString::Printf(TEXT("Cost %.1f kUSD exceeds budget %.1f kUSD"), Budget.CostKUSD, Mission.BudgetKUSD)));

	// Data check (generated <= comms capacity)
	R.bDataOK = Budget.DataRateGbitDay <= Budget.CommsCapacityGbitDay + 0.001f;
	if (!R.bDataOK)
		R.Messages.Add(FText::FromString(FString::Printf(TEXT("Data %.2f Gbit/day exceeds comms capacity %.2f"), Budget.DataRateGbitDay, Budget.CommsCapacityGbitDay)));

	// Comms window (coverage) - soft check: capacity > 0
	R.bCommsOK = Budget.CommsCapacityGbitDay > 0.f;
	if (!R.bCommsOK)
		R.Messages.Add(FText::FromString(TEXT("No communications capacity selected")));

	// Lifetime check
	R.bLifetimeOK = Budget.LifetimeMonths >= Mission.RequiredLifetimeMonths;
	if (!R.bLifetimeOK)
		R.Messages.Add(FText::FromString(FString::Printf(TEXT("Orbit lifetime %d months < required %d months"), Budget.LifetimeMonths, Mission.RequiredLifetimeMonths)));

	return R;
}
