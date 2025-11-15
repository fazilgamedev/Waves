// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_Attack.generated.h"

/**
 * 
 */
UCLASS()
class WAVES_API UBTT_Attack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	UBTT_Attack();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBlackboardKeySelector AttackTarget;

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;

private:

	UFUNCTION()
		void OnMontageEnded(class UAnimMontage* Montage, bool bInterrupted);

	UPROPERTY(EditAnywhere)
		TArray<class UAnimMontage*> AttackMontage;

	UPROPERTY(EditAnywhere)
		bool bWaitForMontageToEnd = true;
	
	int32 i;
	UBehaviorTreeComponent* CachedComp = nullptr;
	class UAnimInstance* CachedAnimInst = nullptr;
};
