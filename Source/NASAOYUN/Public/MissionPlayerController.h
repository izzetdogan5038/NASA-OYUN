// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MissionPlayerController.generated.h"

UCLASS()
class NASAOYUN_API AMissionPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Mission|UI")
	TSubclassOf<class UMissionHUDWidget> HUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Mission|UI")
	TSubclassOf<class UMissionDesignerWidget> DesignerWidgetClass;

protected:
	UPROPERTY() class UMissionHUDWidget* HUDWidget = nullptr;
	UPROPERTY() class UMissionDesignerWidget* DesignerWidget = nullptr;
};
