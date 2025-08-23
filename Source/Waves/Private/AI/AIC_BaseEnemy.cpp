// Fill out your copyright notice in the Description page of Project Settings.

#include "Waves/Public/AI/AIC_BaseEnemy.h"
#include "Waves/Public/Character/BaseEnemy.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

AAIC_BaseEnemy::AAIC_BaseEnemy()
{
	BTComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BTComp"));
}

void AAIC_BaseEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void AAIC_BaseEnemy::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);

	if (!InPawn) return;

	if (!BTAsset) return;

	EnemyREF = Cast<ABaseEnemy>(InPawn);

	FTimerHandle Handle;
	GetWorldTimerManager().SetTimer(Handle, this, &AAIC_BaseEnemy::Temp, 1.f, false);

}

void AAIC_BaseEnemy::Temp()
{
	RunBehaviorTree(BTAsset);

	Blackboard->SetValueAsObject(TEXT("TargetActor"), UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}
