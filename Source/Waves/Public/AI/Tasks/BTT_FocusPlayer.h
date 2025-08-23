// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_FocusPlayer.generated.h"

/**
 * 
 */
UCLASS()
class WAVES_API UBTT_FocusPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	UBTT_FocusPlayer();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBlackboardKeySelector FocusTarget_Key;

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
