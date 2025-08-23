// Fill out your copyright notice in the Description page of Project Settings.

#include "Waves/Public/AI/Tasks/BTT_Attack.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"

UBTT_Attack::UBTT_Attack()
{
	NodeName = TEXT("Attack");
	bCreateNodeInstance = true;
	bNotifyTick = false;
}

EBTNodeResult::Type UBTT_Attack::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	CachedComp = &OwnerComp;
	AAIController* AIC = OwnerComp.GetAIOwner();
	ACharacter* CharREF = Cast<ACharacter>(AIC->GetPawn());
	CachedAnimInst = CharREF->GetMesh()->GetAnimInstance();
	ACharacter* TargetPawn = Cast<ACharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AttackTarget.SelectedKeyName));
	AIC->SetFocus(TargetPawn);
	float Duration = CachedAnimInst->Montage_Play(AttackMontage, 1.f);
	if (Duration <= 0.f) return EBTNodeResult::Failed;
	if (bWaitForMontageToEnd) {
		CachedAnimInst->OnMontageEnded.AddDynamic(this, &UBTT_Attack::OnMontageEnded);
		return EBTNodeResult::InProgress;
	}
	else
	{
		return EBTNodeResult::Succeeded;
	}
}

void UBTT_Attack::OnTaskFinished(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, EBTNodeResult::Type TaskResult)
{
	if (CachedAnimInst) CachedAnimInst->OnMontageEnded.RemoveDynamic(this, &UBTT_Attack::OnMontageEnded);
	CachedAnimInst = nullptr;
	CachedComp = nullptr;
}

void UBTT_Attack::OnMontageEnded(UAnimMontage * Montage, bool bInterrupted)
{
	if (!CachedAnimInst || !CachedComp || Montage != AttackMontage) return;
	if (CachedAnimInst) CachedAnimInst->OnMontageEnded.RemoveDynamic(this, &UBTT_Attack::OnMontageEnded);
	FinishLatentTask(*CachedComp, bInterrupted ? EBTNodeResult::Failed : EBTNodeResult::Succeeded);
	CachedAnimInst = nullptr;
	CachedComp = nullptr;
}
