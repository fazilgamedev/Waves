// Fill out your copyright notice in the Description page of Project Settings.

#include "Waves/Public/Character/BaseEnemy.h"
#include "Waves/Public/Character/Animations/EnemyAnimInst.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Animation/AnimMontage.h"
#include "TimerManager.h"
#include "Waves/Public/AI/AIC_BaseEnemy.h"
#include "BehaviorTree/BehaviorTreeComponent.h"


// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();

	EnemyAnimInst = Cast<UEnemyAnimInst>(GetMesh()->GetAnimInstance());

	AIC = Cast<AAIC_BaseEnemy>(GetController());

}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ABaseEnemy::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (Damage <= 0.f) return 0.f;
	Health -= Damage;
	if (Health <= 0.f) {
		Death();
	}
	return Damage;
}

void ABaseEnemy::OnMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload & BranchingPointPayload)
{
	if (NotifyName == "EnemyDeathNotify") {
		Destroy();
	}
}

void ABaseEnemy::Death()
{
	bIsDead = true;
	AIC->BTComp->StopTree(EBTStopMode::Safe);
	AIC->ClearFocus(EAIFocusPriority::Gameplay);
	int32 i = FMath::RandRange(0, 1);
	if (!DeathMontage[i]) return;
	EnemyAnimInst->Montage_Play(DeathMontage[i], 1.f);
	EnemyAnimInst->Montage_SetNextSection("LoopStart", "LoopStart", DeathMontage[i]);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AIC->StopMovement();
	SetLifeSpan(5.f); 
}
