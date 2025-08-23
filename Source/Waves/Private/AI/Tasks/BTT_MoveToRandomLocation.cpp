// Fill out your copyright notice in the Description page of Project Settings.

#include "Waves/Public/AI/Tasks/BTT_MoveToRandomLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"

UBTT_MoveToRandomLocation::UBTT_MoveToRandomLocation()
{
	NodeName = TEXT("MoveToRandomLocation");
	bCreateNodeInstance = true;
	bNotifyTick = false;
}

EBTNodeResult::Type UBTT_MoveToRandomLocation::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	CachedComp = &OwnerComp;
	AAIController* AIC = OwnerComp.GetAIOwner();
	APawn* AIPawn = AIC->GetPawn();
	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(AIC->GetWorld());
	FNavLocation RandPoint;
	if (!NavSys->GetRandomReachablePointInRadius(AIPawn->GetActorLocation(), 1000.f, RandPoint)) return EBTNodeResult::Failed;
	AIC->ReceiveMoveCompleted.AddDynamic(this, &UBTT_MoveToRandomLocation::OnMoveCompleted);
	EPathFollowingRequestResult::Type ReqResult = AIC->MoveToLocation(RandPoint.Location, 150.f, true, true, true, false, 0, true);
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

void UBTT_MoveToRandomLocation::OnTaskFinished(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, EBTNodeResult::Type TaskResult)
{
	AAIController* AIC = OwnerComp.GetAIOwner();
	if (AIC) AIC->ReceiveMoveCompleted.RemoveDynamic(this, &UBTT_MoveToRandomLocation::OnMoveCompleted);
	CachedComp = nullptr;
}

void UBTT_MoveToRandomLocation::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	if (!CachedComp) return;
	AAIController* AIC = CachedComp->GetAIOwner();
	if (AIC) AIC->ReceiveMoveCompleted.RemoveDynamic(this, &UBTT_MoveToRandomLocation::OnMoveCompleted);
	FinishLatentTask(*CachedComp, (Result == EPathFollowingResult::Success) ? EBTNodeResult::Succeeded : EBTNodeResult::Failed);
	CachedComp = nullptr;
}

