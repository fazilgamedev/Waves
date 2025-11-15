// Fill out your copyright notice in the Description page of Project Settings.

#include "../UI/HUD_Player.h"
#include "../Character/BaseCharacter.h"
#include "../UI/UW_Crosshair.h"
#include "../UI/UW_HealthBar.h"
#include "Blueprint/UserWidget.h"

void AHUD_Player::BeginPlay()
{
	Super::BeginPlay();

	CharacterREF = Cast<ABaseCharacter>(GetOwningPawn());

	if (CrosshairWidgetClass) CrosshairWidget = CreateWidget<UUW_Crosshair>(GetWorld(), CrosshairWidgetClass);
	if (HealthBarWidgetClass) HealthBarWidget = CreateWidget<UUW_HealthBar>(GetWorld(), HealthBarWidgetClass);

	if (!CrosshairWidget || !HealthBarWidget) return;

	HealthBarWidget->CharacterREF = CharacterREF;
	
	CrosshairWidget->AddToViewport(0);
	HealthBarWidget->AddToViewport(0);
}
