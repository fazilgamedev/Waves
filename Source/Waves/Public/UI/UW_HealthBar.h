// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_HealthBar.generated.h"

/**
 * 
 */
UCLASS()
class WAVES_API UUW_HealthBar : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class ABaseCharacter* CharacterREF = nullptr;

	
	
};
