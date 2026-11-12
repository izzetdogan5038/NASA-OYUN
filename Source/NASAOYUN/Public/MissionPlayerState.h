// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MissionTypes.h"
#include "MissionPlayerState.generated.h"

UENUM(BlueprintType)
enum class EMissionRole : uint8
{
	None,
	MissionDirector,
	ScienceLead,
	PowerCommsEngineer,
	OrbitLaunchEngineer
};

UCLASS()
class NASAOYUN_API AMissionPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Mission")
	EMissionRole MissionRole = EMissionRole::None;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Mission")
	float ContributionScore = 0.f;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};

