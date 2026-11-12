// Copyright Epic Games, Inc. All Rights Reserved.

#include "MissionPlayerState.h"
#include "Net/UnrealNetwork.h"

void AMissionPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMissionPlayerState, MissionRole);
	DOREPLIFETIME(AMissionPlayerState, ContributionScore);
}

