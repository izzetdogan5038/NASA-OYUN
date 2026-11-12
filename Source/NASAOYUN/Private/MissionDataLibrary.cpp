// Copyright Epic Games, Inc. All Rights Reserved.

#include "MissionDataLibrary.h"

FInstrumentRow UMissionDataLibrary::GetInstrument(UDataTable* Table, FName Id, bool& bFound)
{
	bFound = false;
	FInstrumentRow R;
	if (Table) { if (const FInstrumentRow* Row = Table->FindRow<FInstrumentRow>(Id, TEXT("GetInstrument"))) { R = *Row; bFound = true; } }
	return R;
}

FBusComponentRow UMissionDataLibrary::GetBusComponent(UDataTable* Table, FName Id, bool& bFound)
{
	bFound = false;
	FBusComponentRow R;
	if (Table) { if (const FBusComponentRow* Row = Table->FindRow<FBusComponentRow>(Id, TEXT("GetBusComponent"))) { R = *Row; bFound = true; } }
	return R;
}

FLaunchVehicleRow UMissionDataLibrary::GetLaunchVehicle(UDataTable* Table, FName Id, bool& bFound)
{
	bFound = false;
	FLaunchVehicleRow R;
	if (Table) { if (const FLaunchVehicleRow* Row = Table->FindRow<FLaunchVehicleRow>(Id, TEXT("GetLaunchVehicle"))) { R = *Row; bFound = true; } }
	return R;
}

FOrbitRow UMissionDataLibrary::GetOrbit(UDataTable* Table, FName Id, bool& bFound)
{
	bFound = false;
	FOrbitRow R;
	if (Table) { if (const FOrbitRow* Row = Table->FindRow<FOrbitRow>(Id, TEXT("GetOrbit"))) { R = *Row; bFound = true; } }
	return R;
}

FMissionRow UMissionDataLibrary::GetMission(UDataTable* Table, FName Id, bool& bFound)
{
	bFound = false;
	FMissionRow R;
	if (Table) { if (const FMissionRow* Row = Table->FindRow<FMissionRow>(Id, TEXT("GetMission"))) { R = *Row; bFound = true; } }
	return R;
}

float UMissionDataLibrary::SumScienceValue(UDataTable* Table, const TArray<FName>& Ids)
{
	float Sum = 0.f;
	if (!Table) return Sum;
	for (const FName& Id : Ids)
	{
		if (const FInstrumentRow* Row = Table->FindRow<FInstrumentRow>(Id, TEXT("SumScienceValue")))
		{
			Sum += Row->ScienceValue;
		}
	}
	return Sum;
}

float UMissionDataLibrary::GetLaunchCapacity(UDataTable* LaunchTable, UDataTable* OrbitTable, FName VehicleId, FName OrbitId, bool& bCompatible)
{
	bCompatible = false;
	float Cap = 0.f;
	if (!LaunchTable || !OrbitTable) return Cap;
	const FLaunchVehicleRow* V = LaunchTable->FindRow<FLaunchVehicleRow>(VehicleId, TEXT("GetLaunchCapacity"));
	const FOrbitRow* O = OrbitTable->FindRow<FOrbitRow>(OrbitId, TEXT("GetLaunchCapacity"));
	if (!V || !O) return Cap;
	// Reachable check
	if (!V->ReachableOrbits.Contains(OrbitId)) return Cap;
	// Simple: LEO capacity scaled by launch cost factor; treat GTO-ish for high orbits
	bCompatible = true;
	Cap = V->PayloadLEOKg / FMath::Max(0.1f, O->LaunchCostFactor);
	return Cap;
}
