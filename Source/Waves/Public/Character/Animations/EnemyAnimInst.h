// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInst.generated.h"

class ABaseEnemy;

/**
 * 
 */
UCLASS()
class WAVES_API UEnemyAnimInst : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	UEnemyAnimInst();

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ABaseEnemy* EnemyREF;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Speed = 0.f;
	
};
