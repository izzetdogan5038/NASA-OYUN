// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MissionTypes.h"
#include "MissionResourceManager.generated.h"

UCLASS(BlueprintType)
class NASAOYUN_API UMissionResourceManager : public UObject
{
	GENERATED_BODY()

public:
	// Compute aggregate resource budget for a design given data tables.
	UFUNCTION(BlueprintCallable, Category = "Mission")
	static FResourceBudget ComputeBudget(
		const FMissionDesign& Design,
		UDataTable* InstrumentTable,
		UDataTable* BusTable,
		UDataTable* LaunchTable,
		UDataTable* OrbitTable);

	UFUNCTION(BlueprintCallable, Category = "Mission")
	static FValidationResult Validate(
		const FMissionDesign& Design,
		const FMissionRow& Mission,
		const FResourceBudget& Budget,
		float LaunchCapacityKg);
};
