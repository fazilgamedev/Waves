// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIC_BaseEnemy.generated.h"

class ABaseEnemy;
class UBehaviorTreeComponent;

/**
 * 
 */
UCLASS()
class WAVES_API AAIC_BaseEnemy : public AAIController
{
	GENERATED_BODY()
	
public:

	AAIC_BaseEnemy();

	UPROPERTY(VisibleAnywhere)
		ABaseEnemy* EnemyREF = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBehaviorTree* BTAsset = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBehaviorTreeComponent* BTComp = nullptr;

	UPROPERTY()
		bool bScreamed = false;

protected:

	virtual void BeginPlay() override;

	virtual void Possess(APawn* InPawn) override;

private:

	UFUNCTION()
		void Temp();

};
