// Fill out your copyright notice in the Description page of Project Settings.

#include "Waves/Public/AI/Tasks/BTT__Scream.h"
#include "Waves/Public/AI/AIC_BaseEnemy.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"

UBTT__Scream::UBTT__Scream()
{
	NodeName = TEXT("Scream");
	bCreateNodeInstance = true;
	bNotifyTick = false;
}

EBTNodeResult::Type UBTT__Scream::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	CachedComp = &OwnerComp;
	AAIController* AIC = OwnerComp.GetAIOwner();
	ACharacter* CharREF = Cast<ACharacter>(AIC->GetPawn());
	CachedAnimInst = CharREF->GetMesh()->GetAnimInstance();
	ACharacter* TargetPawn = Cast<ACharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetActor.SelectedKeyName));
	AIC->SetFocus(TargetPawn);
	float Duration = CachedAnimInst->Montage_Play(ScreamMontage, 1.f);
	if (Duration <= 0.f) return EBTNodeResult::Failed;
	if (bWaitForMontageToEnd) {
		CachedAnimInst->OnMontageEnded.AddDynamic(this, &UBTT__Scream::OnMontageEnded);
		return EBTNodeResult::InProgress;
	}
	else
	{
		return EBTNodeResult::Succeeded;
	}
}

void UBTT__Scream::OnTaskFinished(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, EBTNodeResult::Type TaskResult)
{
	if (CachedAnimInst) CachedAnimInst->OnMontageEnded.RemoveDynamic(this, &UBTT__Scream::OnMontageEnded);
	CachedAnimInst = nullptr;
	CachedComp = nullptr;
}

void UBTT__Scream::OnMontageEnded(UAnimMontage * Montage, bool bInterrupted)
{
	if (!CachedAnimInst || !CachedComp || Montage != ScreamMontage) return;
	if (CachedAnimInst) CachedAnimInst->OnMontageEnded.RemoveDynamic(this, &UBTT__Scream::OnMontageEnded);
	FinishLatentTask(*CachedComp, bInterrupted ? EBTNodeResult::Failed : EBTNodeResult::Succeeded);
	Cast<AAIC_BaseEnemy>(CachedComp->GetAIOwner())->bScreamed = true;
	CachedAnimInst = nullptr;
	CachedComp = nullptr;
}
