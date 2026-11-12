// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MissionTypes.h"
#include "MissionPlayerState.h"
#include "MissionGameInstance.generated.h"

UCLASS()
class NASAOYUN_API UMissionGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "Mission") FMissionDesign CurrentDesign;
	UPROPERTY(BlueprintReadWrite, Category = "Mission") FName SelectedMissionId;
	UPROPERTY(BlueprintReadWrite, Category = "Mission") EMissionRole LocalRole = EMissionRole::MissionDirector;
};
