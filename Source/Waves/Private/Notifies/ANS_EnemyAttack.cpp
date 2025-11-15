// Fill out your copyright notice in the Description page of Project Settings.

#include "../Notifies/ANS_EnemyAttack.h"
#include "../Character/BaseEnemy.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"

void UANS_EnemyAttack::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float Duration)
{
	Super::NotifyBegin(MeshComp, Animation, Duration);
		
	Cast<ABaseEnemy>(MeshComp->GetOwner())->AttackCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

}

void UANS_EnemyAttack::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	Cast<ABaseEnemy>(MeshComp->GetOwner())->AttackCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
