// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ArmsAnimInst.generated.h"

class ABaseCharacter;
class AWeaponMaster;

/**
 * 
 */
UCLASS()
class WAVES_API UArmsAnimInst : public UAnimInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ABaseCharacter* CharacterREF = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Speed = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Direction = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AWeaponMaster* CurrentWeapon = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FTransform SightTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AimAlpha = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FTransform RelativeHandTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FTransform LHIKTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LHIKAlpha = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector SwayVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FRotator OldRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FRotator TurnRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector TurnLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SideMove = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float FrontMove = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FTransform RecoilResetTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FTransform RecoilTransform;

public:

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaTime) override;

	UFUNCTION()
		void SetSightTransform();

	UFUNCTION()
		void SetRelativeHandTransform();
	
	UFUNCTION()
		static FTransform MakeRelativeTransform(FTransform A, FTransform RelativeTo);

	UFUNCTION()
		void SetLHIKTransform();

	UFUNCTION()
		void WalkAnim(float DeltaTime);

	UFUNCTION()
		void HandSway(float DeltaTime);
	UFUNCTION()
		void SideRotation(float _SideMove, float DeltaTime);

	UFUNCTION()
		void FrontRotation(float _FrontMove, float DeltaTime);

	UFUNCTION()
		void InterpRecoil(float DeltaTime);

	UFUNCTION()
		void InterpResetRecoil(float DeltaTime);

	UFUNCTION()
		void Firing();
	
	
};
