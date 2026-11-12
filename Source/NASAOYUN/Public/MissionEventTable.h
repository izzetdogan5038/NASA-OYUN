// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MissionTypes.h"
#include "MissionEventTable.generated.h"

// Row for random mission events DataTable
USTRUCT(BlueprintType)
struct FMissionEventRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite) FName EventId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FText Title;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FText Description;
	// Probability per month (0..1)
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float Probability = 0.1f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float Severity = 0.3f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float PowerDeltaW = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float DataLossGbit = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float ReliabilityHit = 0.f;
	// Minimum tech level / difficulty gate
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 MinDifficulty = 1;
};
