// Copyright Epic Games, Inc. All Rights Reserved.

#include "MissionPlayerController.h"
#include "MissionWidgets.h"
#include "Blueprint/UserWidget.h"

void AMissionPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController())
	{
		if (HUDWidgetClass)
		{
			HUDWidget = CreateWidget<UMissionHUDWidget>(this, HUDWidgetClass);
			if (HUDWidget) HUDWidget->AddToViewport(0);
		}
		else
		{
			HUDWidget = CreateWidget<UMissionHUDWidget>(this, UMissionHUDWidget::StaticClass());
			if (HUDWidget) HUDWidget->AddToViewport(0);
		}

		if (DesignerWidgetClass)
		{
			DesignerWidget = CreateWidget<UMissionDesignerWidget>(this, DesignerWidgetClass);
		}
		else
		{
			DesignerWidget = CreateWidget<UMissionDesignerWidget>(this, UMissionDesignerWidget::StaticClass());
		}
		if (DesignerWidget)
		{
			DesignerWidget->AddToViewport(1);
		}
	}
}
