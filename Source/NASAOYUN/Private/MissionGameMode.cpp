// Copyright Epic Games, Inc. All Rights Reserved.

#include "MissionGameMode.h"
#include "Engine/DataTable.h"

AMissionGameMode::AMissionGameMode()
{
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
	// Simulation tick & random events handled by MissionSim subsystem (TODO)
}

void AMissionGameMode::EvaluateMission()
{
	SetPhase(EMissionPhase::Evaluation);
	// Scoring logic (TODO): combine science, efficiency, reliability, collaboration
	FinalScore.TotalScore = FinalScore.ScienceScore + FinalScore.EfficiencyScore + FinalScore.ReliabilityScore + FinalScore.CollaborationScore;
	SetPhase(EMissionPhase::Complete);
}
