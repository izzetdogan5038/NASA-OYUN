// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MissionTypes.generated.h"

// ---- Resource budget for a mission design ----
USTRUCT(BlueprintType)
struct FResourceBudget
{
	GENERATED_BODY()

	// Total spacecraft mass (kg) - must be <= launch vehicle capacity
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float MassKg = 0.f;
	// Power generated (W)
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float PowerGenW = 0.f;
	// Power consumed (W)
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float PowerDrawW = 0.f;
	// Total cost (USD thousands)
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float CostKUSD = 0.f;
	// Data generated (Gbit/day)
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float DataRateGbitDay = 0.f;
	// Communications capacity (Gbit/day)
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float CommsCapacityGbitDay = 0.f;
	// Planned mission lifetime (months)
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 LifetimeMonths = 0;
};

// ---- Scientific instrument (payload) ----
USTRUCT(BlueprintType)
struct FInstrumentRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite) FName InstrumentId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FText DisplayName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FText Description;
	// Mass (kg)
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float MassKg = 1.f;
	// Power draw (W)
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float PowerDrawW = 5.f;
	// Cost (USD thousands)
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float CostKUSD = 10.f;
	// Data generated (Gbit/day)
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float DataRateGbitDay = 1.f;
	// Scientific value score (0-100)
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float ScienceValue = 10.f;
	// Minimum tech level required (1-3)
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 TechLevel = 1;
	// Which mission objectives this serves (tags)
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FName> ObjectiveTags;
};

// ---- Spacecraft bus component ----
UENUM(BlueprintType)
enum class EBusCategory : uint8
{
	Structure,
	PowerGeneration,   // solar panels
	PowerStorage,      // batteries
	Communications,
	ADCS,              // attitude control
	OBC,               // onboard computer
	Thermal,
	Propulsion
};

USTRUCT(BlueprintType)
struct FBusComponentRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite) FName ComponentId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FText DisplayName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FText Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) EBusCategory Category = EBusCategory::Structure;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float MassKg = 1.f;
	// Positive = generation, negative/positive draw handled by type
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float PowerGenW = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float PowerDrawW = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float CostKUSD = 10.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float DataCapacityGbitDay = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float Reliability = 1.f; // 0..1
};

// ---- Launch vehicle ----
USTRUCT(BlueprintType)
struct FLaunchVehicleRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite) FName VehicleId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FText DisplayName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FText Description;
	// Payload capacity to LEO (kg)
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float PayloadLEOKg = 1000.f;
	// Payload capacity to GTO (kg)
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float PayloadGTOkg = 0.f;
	// Cost (USD millions)
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float CostMUSD = 50.f;
	// Orbits this vehicle can reach
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FName> ReachableOrbits;
};

// ---- Orbit ----
USTRUCT(BlueprintType)
struct FOrbitRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite) FName OrbitId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FText DisplayName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FText Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float AltitudeKm = 400.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float InclinationDeg = 0.f;
	// Coverage quality 0..1
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float Coverage = 0.5f;
	// Comms window fraction 0..1
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float CommsWindow = 0.5f;
	// Expected lifetime months
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 ExpectedLifetimeMonths = 60;
	// Launch delta-v cost factor (multiplier)
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float LaunchCostFactor = 1.f;
};

// ---- Mission scenario ----
USTRUCT(BlueprintType)
struct FMissionRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite) FName MissionId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FText DisplayName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FText Description;
	// Budget cap (USD thousands)
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float BudgetKUSD = 5000.f;
	// Mass cap (kg) - derived from launch but can be overridden
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float MassCapKg = 2000.f;
	// Required minimum science value
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float MinScienceValue = 50.f;
	// Required mission lifetime (months)
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 RequiredLifetimeMonths = 12;
	// Objective tags that instruments should match
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FName> ObjectiveTags;
	// Difficulty 1-3
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Difficulty = 1;
};

// ---- Runtime mission design (assembled by player) ----
USTRUCT(BlueprintType)
struct FMissionDesign
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite) FName MissionId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FName LaunchVehicleId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FName OrbitId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FName> BusComponentIds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FName> InstrumentIds;
};

// ---- Validation result ----
USTRUCT(BlueprintType)
struct FValidationResult
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bMassOK = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bPowerOK = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bBudgetOK = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bDataOK = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bCommsOK = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bLifetimeOK = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FText> Messages;

	bool IsFullyValid() const
	{
		return bMassOK && bPowerOK && bBudgetOK && bDataOK && bCommsOK && bLifetimeOK;
	}
};

// ---- Final score ----
USTRUCT(BlueprintType)
struct FMissionScore
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite) float ScienceScore = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float EfficiencyScore = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float ReliabilityScore = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float CollaborationScore = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float TotalScore = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FText Grade;
};
