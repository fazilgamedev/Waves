// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT__Scream.generated.h"

/**
 * 
 */
UCLASS()
class WAVES_API UBTT__Scream : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:

	UBTT__Scream();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBlackboardKeySelector TargetActor;

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;

private:

	UFUNCTION()
		void OnMontageEnded(class UAnimMontage* Montage, bool bInterrupted);

	UPROPERTY(EditAnywhere)
		class UAnimMontage*	ScreamMontage = nullptr;

	UPROPERTY(EditAnywhere)
		bool bWaitForMontageToEnd = true;

	UBehaviorTreeComponent* CachedComp = nullptr;
	class UAnimInstance* CachedAnimInst = nullptr;
	
};
