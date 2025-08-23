// ill out your copyright notice in the Description page of Project Settings.

#include "Waves/Public/AI/Decorators/BTD_CanAttackPlayer.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTD_CanAttackPlayer::UBTD_CanAttackPlayer()
{
	NodeName = TEXT("CanAttackPlayer");
}

bool UBTD_CanAttackPlayer::CalculateRawConditionValue(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) const
{
	APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!AIPawn) return false;
	AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetActor_Key.SelectedKeyName));
	if (!TargetActor) return false;
	
	if (FVector::DistSquared(AIPawn->GetActorLocation(), TargetActor->GetActorLocation()) > FMath::Square(150.f)) return false;
	if (!OwnerComp.GetAIOwner()->LineOfSightTo(TargetActor)) return false;

	return true;
}
