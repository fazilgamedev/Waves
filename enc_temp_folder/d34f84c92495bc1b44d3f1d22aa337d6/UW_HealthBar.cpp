// Fill out your copyright notice in the Description page of Project Settings.

#include "UW_HealthBar.h"
#include "../Character/BaseCharacter.h"
#include "../Interface/DamageInterface.h"
#include "Components/ProgressBar.h"

void UUW_HealthBar::NativeConstruct()
{
	Super::NativeConstruct();

}

void UUW_HealthBar::NativeTick(const FGeometry & Geometry, float InDeltaTime)
{
	Super::NativeTick(Geometry, InDeltaTime);

}

float UUW_HealthBar::UpdateHealth() const
{
	if (!CharacterREF) return 0.f;
	return FMath::Clamp((IDamageInterface::Execute_GetCurrentHealth(CharacterREF) / IDamageInterface::Execute_GetMaxHealth(CharacterREF)) * 100.f, 0.f, 100.f);
}
