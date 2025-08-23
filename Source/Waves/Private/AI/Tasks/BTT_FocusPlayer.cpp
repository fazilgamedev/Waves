// Fill out your copyright notice in the Description page of Project Settings.

#include "Waves/Public/AI/Tasks/BTT_FocusPlayer.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTT_FocusPlayer::UBTT_FocusPlayer()
{
	NodeName = TEXT("FocusPlayer");
}

EBTNodeResult::Type UBTT_FocusPlayer::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	OwnerComp.GetAIOwner()->SetFocus(Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FocusTarget_Key.SelectedKeyName)), 0);
	return EBTNodeResult::Succeeded;
}
