// Copyright Epic Games, Inc. All Rights Reserved.

#include "MissionScoringLibrary.h"

FMissionScore UMissionScoringLibrary::ComputeScore(
	const FMissionRow& Mission,
	const FMissionDesign& /*Design*/,
	const FResourceBudget& Budget,
	const FValidationResult& Validation,
	float Reliability,
	float DataCollectedGbit,
	int32 NumInstruments,
	float InstrumentScienceSum)
{
	FMissionScore S;

	// Science: instrument value scaled by validation + data collected
	const float ValidFactor = Validation.IsFullyValid() ? 1.f : 0.4f;
	const float DataFactor = FMath::Clamp(DataCollectedGbit / FMath::Max(1.f, Mission.MinScienceValue * 10.f), 0.f, 1.5f);
	S.ScienceScore = InstrumentScienceSum * ValidFactor * (0.5f + 0.5f * DataFactor);

	// Efficiency: lower waste = higher. Compare used mass/budget vs caps.
	const float MassEff = 1.f - FMath::Clamp(Budget.MassKg / FMath::Max(1.f, Mission.MassCapKg), 0.f, 1.f) * 0.5f;
	const float BudgetEff = 1.f - FMath::Clamp(Budget.CostKUSD / FMath::Max(1.f, Mission.BudgetKUSD), 0.f, 1.f) * 0.5f;
	S.EfficiencyScore = (MassEff + BudgetEff) * 50.f;

	// Reliability: from simulation
	S.ReliabilityScore = Reliability * 50.f;

	// Collaboration: placeholder (set by team mode); default neutral
	S.CollaborationScore = 25.f;

	S.TotalScore = S.ScienceScore + S.EfficiencyScore + S.ReliabilityScore + S.CollaborationScore;
	S.Grade = ScoreToGrade(S.TotalScore);
	return S;
}

FText UMissionScoringLibrary::ScoreToGrade(float TotalScore)
{
	if (TotalScore >= 220.f) return FText::FromString(TEXT("S - Outstanding"));
	if (TotalScore >= 180.f) return FText::FromString(TEXT("A - Excellent"));
	if (TotalScore >= 140.f) return FText::FromString(TEXT("B - Good"));
	if (TotalScore >= 100.f) return FText::FromString(TEXT("C - Adequate"));
	if (TotalScore >= 60.f) return FText::FromString(TEXT("D - Marginal"));
	return FText::FromString(TEXT("F - Mission Failed"));
}
