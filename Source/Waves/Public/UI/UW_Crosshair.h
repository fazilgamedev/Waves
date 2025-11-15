// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_Crosshair.generated.h"

/**
 * 
 */
UCLASS()
class WAVES_API UUW_Crosshair : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UWidgetAnimation* Crosshair = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UWidgetAnimation* Fade = nullptr;

protected:

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& Geometry, float InDeltaTime) override;

private:

	UFUNCTION()
		void GetAnims();
	
	
};
