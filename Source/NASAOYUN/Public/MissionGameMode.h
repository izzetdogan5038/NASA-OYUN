// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MissionTypes.h"
#include "MissionGameState.h"
#include "MissionPlayerState.h"
#include "MissionGameMode.generated.h"

UENUM(BlueprintType)
enum class EMissionPhase : uint8
{
	Briefing,
	Design,
	Validation,
	Simulation,
	Evaluation,
	Complete
};

UCLASS()
class NASAOYUN_API AMissionGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMissionGameMode();

	UPROPERTY(BlueprintReadOnly, Category = "Mission")
	EMissionPhase CurrentPhase = EMissionPhase::Briefing;

	UPROPERTY(BlueprintReadOnly, Category = "Mission")
	FMissionDesign CurrentDesign;

	UPROPERTY(BlueprintReadOnly, Category = "Mission")
	FMissionScore FinalScore;

	UFUNCTION(BlueprintCallable, Category = "Mission")
	void SetPhase(EMissionPhase NewPhase);

	UFUNCTION(BlueprintCallable, Category = "Mission")
	void StartSimulation();

	UFUNCTION(BlueprintCallable, Category = "Mission")
	void EvaluateMission();

protected:
	virtual void BeginPlay() override;
};
