// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MissionTypes.h"
#include "MissionSimulationSubsystem.generated.h"

// A random event that can occur during simulation
USTRUCT(BlueprintType)
struct FSimEvent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite) FName EventId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FText Title;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FText Description;
	// Severity 0..1
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float Severity = 0.3f;
	// Effects applied to the running mission
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float PowerDeltaW = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float DataLossGbit = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float ReliabilityHit = 0.f;
};

UCLASS()
class NASAOYUN_API UMissionSimulationSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	// Run a full simulation for the given design over N months. Returns events + final score inputs.
	UFUNCTION(BlueprintCallable, Category = "Mission|Sim")
	void RunSimulation(const FMissionDesign& Design, const FMissionRow& Mission, int32 MonthsToSimulate, const FResourceBudget& Budget);

	// Last run results
	UPROPERTY(BlueprintReadOnly, Category = "Mission|Sim")
	TArray<FSimEvent> LastEvents;

	UPROPERTY(BlueprintReadOnly, Category = "Mission|Sim")
	float LastReliability = 1.f;

	UPROPERTY(BlueprintReadOnly, Category = "Mission|Sim")
	float LastDataCollectedGbit = 0.f;

protected:
	void TickMonth(int32 Month, const FMissionDesign& Design, const FMissionRow& Mission, const FResourceBudget& Budget);
};
