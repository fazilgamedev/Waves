// Fill out your copyright notice in the Description page of Project Settings.

#include "Waves/Public/AI/Decorators/BTD_ShouldScream.h"
#include "Waves/Public/AI/AIC_BaseEnemy.h"

UBTD_ShouldScream::UBTD_ShouldScream()
{
	NodeName = TEXT("ShouldScream");
}

bool UBTD_ShouldScream::CalculateRawConditionValue(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) const
{
	return !Cast<AAIC_BaseEnemy>(OwnerComp.GetAIOwner())->bScreamed;
}
