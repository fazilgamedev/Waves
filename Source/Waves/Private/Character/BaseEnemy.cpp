// Fill out your copyright notice in the Description page of Project Settings.

#include "Waves/Public/Character/BaseEnemy.h"
#include "Waves/Public/Character/Animations/EnemyAnimInst.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Animation/AnimMontage.h"
#include "TimerManager.h"
#include "Waves/Public/AI/AIC_BaseEnemy.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "../Component/DamageSystem.h"


// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DamageSystem = CreateDefaultSubobject<UDamageSystem>(TEXT("DamageSystem"));
	DamageSystem->OnDeath.AddDynamic(this, &ABaseEnemy::Death);
	DamageSystem->OnBlocked.AddDynamic(this, &ABaseEnemy::Blocked);
	DamageSystem->OnDamageResponse.AddDynamic(this, &ABaseEnemy::DamageResponse);
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

float ABaseEnemy::GetCurrentHealth_Implementation()
{
	return DamageSystem->Health;
}

float ABaseEnemy::GetMaxHealth_Implementation()
{
	return DamageSystem->MaxHealth;
}

float ABaseEnemy::Heal_Implementation(float Amount)
{
	return DamageSystem->Heal(Amount);
}

bool ABaseEnemy::TakeDamage_Implementation(FDamageInfo DamageInfo)
{
	return DamageSystem->TakeDamage(DamageInfo);
}

void ABaseEnemy::OnMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload & BranchingPointPayload)
{
	if (NotifyName == "EnemyDeathNotify") {
		Destroy();
	}
}

void ABaseEnemy::Death()
{
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

void ABaseEnemy::Blocked(bool bCanBeParried)
{
	UE_LOG(LogTemp, Warning, TEXT("Parried"));
}

void ABaseEnemy::DamageResponse(EDamageResponse DamageResponse)
{

	UE_LOG(LogTemp, Warning, TEXT("RESPONSE"));
}
