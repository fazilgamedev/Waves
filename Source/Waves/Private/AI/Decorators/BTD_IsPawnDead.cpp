// Fill out your copyright notice in the Description page of Project Settings.

#include "Waves/Public/AI/Decorators/BTD_IsPawnDead.h"
#include "Waves/Public/Character/BaseEnemy.h"
#include "../Component/DamageSystem.h"
#include "AIController.h"

UBTD_IsPawnDead::UBTD_IsPawnDead()
{
	NodeName = TEXT("IsPawnDead");
}

bool UBTD_IsPawnDead::CalculateRawConditionValue(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) const
{
	return Cast<ABaseEnemy>(OwnerComp.GetAIOwner()->GetPawn())->DamageSystem->bIsDead;
}
