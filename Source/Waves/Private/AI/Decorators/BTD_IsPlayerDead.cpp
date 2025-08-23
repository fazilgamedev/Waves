// Fill out your copyright notice in the Description page of Project Settings.

#include "Waves/Public/AI/Decorators/BTD_IsPlayerDead.h"
#include "Waves/Public/Character/BaseCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTD_IsPlayerDead::UBTD_IsPlayerDead()
{
	NodeName = TEXT("IsPlayerDead");
}

bool UBTD_IsPlayerDead::CalculateRawConditionValue(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) const
{
	return Cast<ABaseCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetActor_Key.SelectedKeyName))->bIsDead;
}
