// Fill out your copyright notice in the Description page of Project Settings.

#include "Waves/Public/AI/Tasks/BTT_ClearFocus.h"
#include "AIController.h"

UBTT_ClearFocus::UBTT_ClearFocus()
{
	NodeName = TEXT("ClearFocus");
}

EBTNodeResult::Type UBTT_ClearFocus::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{	
	OwnerComp.GetAIOwner()->ClearFocus(EAIFocusPriority::Default);
	return EBTNodeResult::Succeeded;
}
