// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_HealthBar.generated.h"

class UProgressBar;

/**
 * 
 */
UCLASS()
class WAVES_API UUW_HealthBar : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& Geometry, float InDeltaTime) override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class ABaseCharacter* CharacterREF = nullptr;

	UPROPERTY(meta = (BindWidget))
		UProgressBar* HealthBar = nullptr;

	UFUNCTION(BlueprintPure)
		float UpdateHealth() const;
	   	
	
};
