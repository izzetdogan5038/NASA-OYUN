// Copyright Epic Games, Inc. All Rights Reserved.

#include "MissionGameMode.h"
#include "NASAOYUN.h"
#include "Engine/DataTable.h"

AMissionGameMode::AMissionGameMode()
{
	GameStateClass = AMissionGameState::StaticClass();
	PlayerStateClass = AMissionPlayerState::StaticClass();
}

void AMissionGameMode::BeginPlay()
{
	Super::BeginPlay();
	SetPhase(EMissionPhase::Briefing);
}

void AMissionGameMode::SetPhase(EMissionPhase NewPhase)
{
	CurrentPhase = NewPhase;
	UE_LOG(LogMission, Log, TEXT("Mission phase -> %d"), (int32)NewPhase);
}

void AMissionGameMode::StartSimulation()
{
	SetPhase(EMissionPhase::Simulation);
}

void AMissionGameMode::EvaluateMission()
{
	SetPhase(EMissionPhase::Evaluation);
	FinalScore.TotalScore = FinalScore.ScienceScore + FinalScore.EfficiencyScore + FinalScore.ReliabilityScore + FinalScore.CollaborationScore;
	SetPhase(EMissionPhase::Complete);
}

