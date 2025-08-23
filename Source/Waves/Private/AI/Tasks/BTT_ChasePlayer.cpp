// Fill out your copyright notice in the Description page of Project Settings.

#include "Waves/Public/AI/Tasks/BTT_ChasePlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UBTT_ChasePlayer::UBTT_ChasePlayer()
{
	NodeName = TEXT("ChasePlayer");
	bNotifyTick = false;
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTT_ChasePlayer::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	CachedComp = &OwnerComp;
	AAIController* AIC = OwnerComp.GetAIOwner();
	APawn* Pawn = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ChaseTarget_Key.SelectedKeyName));
	AIC->ClearFocus(EAIFocusPriority::Gameplay);
	AIC->ReceiveMoveCompleted.AddDynamic(this, &UBTT_ChasePlayer::OnMoveCompleted);
	auto ReqResult = AIC->MoveToActor(Pawn, 25.f, true, true, false, 0, true);
	switch (ReqResult)
	{
	case EPathFollowingRequestResult::Failed:
		return EBTNodeResult::Failed;
	case EPathFollowingRequestResult::AlreadyAtGoal:
		return EBTNodeResult::Succeeded;
	case EPathFollowingRequestResult::RequestSuccessful:
		return EBTNodeResult::InProgress;
	default:
		return EBTNodeResult::Failed;
	}
}

void UBTT_ChasePlayer::OnTaskFinished(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, EBTNodeResult::Type TaskResult)
{
	AAIController* AIC = OwnerComp.GetAIOwner();
	if (AIC) AIC->ReceiveMoveCompleted.RemoveDynamic(this, &UBTT_ChasePlayer::OnMoveCompleted);
	CachedComp = nullptr;
}

void UBTT_ChasePlayer::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	if (!CachedComp) return;
	AAIController* AIC = CachedComp->GetAIOwner();
	if (AIC) AIC->ReceiveMoveCompleted.RemoveDynamic(this, &UBTT_ChasePlayer::OnMoveCompleted);
	FinishLatentTask(*CachedComp, (Result == EPathFollowingResult::Success) ? EBTNodeResult::Succeeded : EBTNodeResult::Failed);
	CachedComp = nullptr;
}
