// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUD_Player.generated.h"

class UUW_Crosshair;
class UUW_HealthBar;

/**
 * 
 */
UCLASS()
class WAVES_API AHUD_Player : public AHUD
{
	GENERATED_BODY()
	
public:

	UPROPERTY()
		class ABaseCharacter* CharacterREF = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UUW_Crosshair> CrosshairWidgetClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UUW_HealthBar> HealthBarWidgetClass = nullptr;

	UPROPERTY()
		UUW_Crosshair* CrosshairWidget = nullptr;

	UPROPERTY()
		UUW_HealthBar* HealthBarWidget = nullptr;

protected:

	virtual void BeginPlay() override;
	
};
