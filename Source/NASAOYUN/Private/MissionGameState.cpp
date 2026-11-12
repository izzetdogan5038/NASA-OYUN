// Copyright Epic Games, Inc. All Rights Reserved.

#include "MissionGameState.h"
#include "Net/UnrealNetwork.h"

void AMissionGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMissionGameState, SharedDesign);
	DOREPLIFETIME(AMissionGameState, bDesignLocked);
}
