// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MissionTypes.h"
#include "MissionDataLibrary.generated.h"

UCLASS()
class NASAOYUN_API UMissionDataLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Mission|Data")
	static FInstrumentRow GetInstrument(UDataTable* Table, FName Id, bool& bFound);

	UFUNCTION(BlueprintCallable, Category = "Mission|Data")
	static FBusComponentRow GetBusComponent(UDataTable* Table, FName Id, bool& bFound);

	UFUNCTION(BlueprintCallable, Category = "Mission|Data")
	static FLaunchVehicleRow GetLaunchVehicle(UDataTable* Table, FName Id, bool& bFound);

	UFUNCTION(BlueprintCallable, Category = "Mission|Data")
	static FOrbitRow GetOrbit(UDataTable* Table, FName Id, bool& bFound);

	UFUNCTION(BlueprintCallable, Category = "Mission|Data")
	static FMissionRow GetMission(UDataTable* Table, FName Id, bool& bFound);

	// Sum science value of selected instruments
	UFUNCTION(BlueprintCallable, Category = "Mission|Data")
	static float SumScienceValue(UDataTable* Table, const TArray<FName>& Ids);

	// Launch capacity for a vehicle to an orbit (kg). Returns 0 if incompatible.
	UFUNCTION(BlueprintCallable, Category = "Mission|Data")
	static float GetLaunchCapacity(UDataTable* LaunchTable, UDataTable* OrbitTable, FName VehicleId, FName OrbitId, bool& bCompatible);
};
