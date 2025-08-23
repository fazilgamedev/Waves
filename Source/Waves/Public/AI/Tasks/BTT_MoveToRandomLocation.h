// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Navigation/PathFollowingComponent.h"
#include "BTT_MoveToRandomLocation.generated.h"

/**
 * 
 */
UCLASS()
class WAVES_API UBTT_MoveToRandomLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	UBTT_MoveToRandomLocation();
	
protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;

private:

	UFUNCTION()
		void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result);

	UBehaviorTreeComponent* CachedComp = nullptr;
};
