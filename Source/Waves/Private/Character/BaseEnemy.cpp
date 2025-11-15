// Fill out your copyright notice in the Description page of Project Settings.

#include "../Character/BaseEnemy.h"
#include "../Character/Animations/EnemyAnimInst.h"
#include "../AI/AIC_BaseEnemy.h"
#include "../Component/DamageSystem.h"
#include "../Interface/DamageInterface.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Animation/AnimMontage.h"
#include "TimerManager.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Components/CapsuleComponent.h"



// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DamageSystem = CreateDefaultSubobject<UDamageSystem>(TEXT("DamageSystem"));
	DamageSystem->OnDeath.AddDynamic(this, &ABaseEnemy::Death);
	DamageSystem->OnBlocked.AddDynamic(this, &ABaseEnemy::Blocked);
	DamageSystem->OnDamageResponse.AddDynamic(this, &ABaseEnemy::DamageResponse);

	AttackCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("AttackCollider"));
	AttackCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttackCollider->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	AttackCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	AttackCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();

	EnemyAnimInst = Cast<UEnemyAnimInst>(GetMesh()->GetAnimInstance());

	AIC = Cast<AAIC_BaseEnemy>(GetController());

	AttackCollider->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "RightHand");
	AttackCollider->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
	AttackCollider->SetRelativeLocation(FVector(0.f, -45.f, 0.f));
	AttackCollider->OnComponentBeginOverlap.AddDynamic(this, &ABaseEnemy::OnWeaponOverlap);

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

void ABaseEnemy::OnWeaponOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->ActorHasTag("Player") && OtherActor->GetClass()->ImplementsInterface(UDamageInterface::StaticClass())) {
		FDamageInfo DI;
		DI.Amount = 20.f;
		DI.DamageResponse = EDamageResponse::HitReaction;
		DI.DamageType = EDamageType::Melee;
		IDamageInterface::Execute_TakeDamage(OtherActor, DI);
	}
}
