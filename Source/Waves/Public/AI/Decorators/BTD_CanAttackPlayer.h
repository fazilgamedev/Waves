// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTD_CanAttackPlayer.generated.h"

/**
 * 
 */
UCLASS()
class WAVES_API UBTD_CanAttackPlayer : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
	
public:

	UBTD_CanAttackPlayer();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBlackboardKeySelector TargetActor_Key;

protected:

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
