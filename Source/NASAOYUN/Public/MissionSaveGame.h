// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MissionTypes.h"
#include "MissionSaveGame.generated.h"

UCLASS()
class NASAOYUN_API UMissionSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = "Mission") FString SaveSlotName = TEXT("MissionDesign");
	UPROPERTY(VisibleAnywhere, Category = "Mission") uint32 UserIndex = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mission") FMissionDesign Design;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mission") FMissionScore Score;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mission") FDateTime SavedAt;
};
