// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseEnemy.generated.h"

class UEnemyAnimInst;
class UAnimMontage;
class AAIC_BaseEnemy;

UCLASS()
class WAVES_API ABaseEnemy : public ACharacter
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
		float MaxHealth = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Health = MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsDead = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UAnimMontage*> DeathMontage;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
		void OnMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);

	UFUNCTION()
		void Death();

	   	  	
};
