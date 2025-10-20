// Fill out your copyright notice in the Description page of Project Settings.

#include "../Component/DamageSystem.h"


// Sets default values for this component's properties
UDamageSystem::UDamageSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDamageSystem::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UDamageSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UDamageSystem::Heal(float Amount)
{
	if (bIsDead) return 0.f;
	Health = FMath::Clamp(Health + Amount, 0.f, MaxHealth);
	return Health;
}

bool UDamageSystem::TakeDamage(FDamageInfo DamageInfo)
{
	switch (CanBeDamaged(DamageInfo.bShouldDamageInvincible, DamageInfo.bCanBeBlocked))
	{
	case ECanBeDamaged::BlockDamage:
		OnBlocked.Broadcast(DamageInfo.bCanBeParried);
		return false;

	case ECanBeDamaged::DoDamage:
		Health = Health - DamageInfo.Amount;
		if (Health <= 0.f) {
			bIsDead = true;
			OnDeath.Broadcast();
			return true;
		}
		else if (bIsInterruptable || DamageInfo.bShouldForceInterrupt) {
			OnDamageResponse.Broadcast(DamageInfo.DamageResponse);
			return true;
		}

	case ECanBeDamaged::NoDamage:
		return false;

	default:
		return false;
	}
	return false;
}

UDamageSystem::ECanBeDamaged UDamageSystem::CanBeDamaged(bool bShouldDamageInvincible, bool bCanBeBlocked)
{
	if (!bIsDead && !(bIsInvincible || bShouldDamageInvincible)) {
		if (bIsBlocking && bCanBeBlocked) {
			return ECanBeDamaged::BlockDamage;
		}
		else {
			return ECanBeDamaged::DoDamage;
		}
	}
	else {
		return ECanBeDamaged::NoDamage;
	}
}

