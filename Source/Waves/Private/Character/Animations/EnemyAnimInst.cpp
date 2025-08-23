// Fill out your copyright notice in the Description page of Project Settings.

#include "Waves/Public/Character/Animations/EnemyAnimInst.h"
#include "Waves/Public/Character/BaseEnemy.h"

UEnemyAnimInst::UEnemyAnimInst()
{

}

void UEnemyAnimInst::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	EnemyREF = Cast<ABaseEnemy>(TryGetPawnOwner());
	if (!EnemyREF) return;

}

void UEnemyAnimInst::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (!EnemyREF) return;

	Speed = EnemyREF->GetVelocity().Size2D();
}

