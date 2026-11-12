// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MissionTypes.h"
#include "MissionGameState.generated.h"

UCLASS()
class NASAOYUN_API AMissionGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Mission")
	FMissionDesign SharedDesign;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Mission")
	bool bDesignLocked = false;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
