// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MissionTypes.h"
#include "MissionScoringLibrary.generated.h"

UCLASS()
class NASAOYUN_API UMissionScoringLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// Compute final mission score from design + simulation results.
	UFUNCTION(BlueprintCallable, Category = "Mission|Score")
	static FMissionScore ComputeScore(
		const FMissionRow& Mission,
		const FMissionDesign& Design,
		const FResourceBudget& Budget,
		const FValidationResult& Validation,
		float Reliability,
		float DataCollectedGbit,
		int32 NumInstruments,
		float InstrumentScienceSum);

	// Convert total score to a letter grade.
	UFUNCTION(BlueprintCallable, Category = "Mission|Score")
	static FText ScoreToGrade(float TotalScore);
};
