// Fill out your copyright notice in the Description page of Project Settings.

#include "Waves/Public/UI/HUD_Player.h"
#include "Waves/Public/Character/BaseCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Waves/Public/UI/UW_Crosshair.h"

void AHUD_Player::BeginPlay()
{
	Super::BeginPlay();

	CharacterREF = Cast<ABaseCharacter>(GetOwningPawn());

	if (CrosshairWidgetClass) CrosshairWidget = CreateWidget<UUW_Crosshair>(GetWorld(), CrosshairWidgetClass);

	//CrosshairWidget->CharacterREF = CharacterREF;

	CrosshairWidget->AddToViewport(0);
}
