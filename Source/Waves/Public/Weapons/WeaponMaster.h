// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Structure/DamageInfo.h"
#include "WeaponMaster.generated.h"

class USkeletalMeshComponent;
class UAnimSequence;
class UParticleSystem;

UENUM(BlueprintType)
enum class EWeaponName : uint8 {
	Unarmed,
	AK47,
	G17
};

UCLASS()
class WAVES_API AWeaponMaster : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponMaster();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* WeaponModel = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimSequence* FireSeq = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UParticleSystem*> HitEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EDamageType DamageType = EDamageType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EDamageResponse DamageResponse = EDamageResponse::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Damage = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Range = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float FireRate = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AimOffset = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ADSFOV = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName SocketToAttach;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EWeaponName WeaponName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float VerticalRecoil = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float HorizontalRecoil = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SideRecoil = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float FrontRecoil = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float RightRecoil = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float UpRecoil = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Recoil_Vertical = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Recoil_Horizontal_Left = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Recoil_Horizontal_Right = 0.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
