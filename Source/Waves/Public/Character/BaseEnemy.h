// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Interface/DamageInterface.h"
#include "../Structure/DamageInfo.h"
#include "BaseEnemy.generated.h"

class UEnemyAnimInst;
class UAnimMontage;
class AAIC_BaseEnemy;

UCLASS()
class WAVES_API ABaseEnemy : public ACharacter, public IDamageInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseEnemy();

	UPROPERTY()
		UEnemyAnimInst* EnemyAnimInst = nullptr;

	UPROPERTY()
		AAIC_BaseEnemy* AIC = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UDamageSystem* DamageSystem = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UAnimMontage*> DeathMontage;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float GetCurrentHealth_Implementation() override;

	virtual float GetMaxHealth_Implementation() override;

	virtual float Heal_Implementation(float Amount) override;

	virtual bool TakeDamage_Implementation(FDamageInfo DamageInfo) override;

	UFUNCTION()
		void OnMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);

	UFUNCTION()
		void Death();

	UFUNCTION()
		void Blocked(bool bCanBeParried);

	UFUNCTION()
		void DamageResponse(EDamageResponse DamageResponse);

	   	  	
};
