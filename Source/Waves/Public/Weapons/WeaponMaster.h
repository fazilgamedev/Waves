// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponMaster.generated.h"

class USkeletalMeshComponent;

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
		USkeletalMeshComponent* WeaponModel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float FireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AimOffset = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ADSFOV = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName SocketToAttach;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EWeaponName WeaponName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float VerticalRecoil;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float HorizontalRecoil;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SideRecoil;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float FrontRecoil;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float RightRecoil;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float UpRecoil;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Recoil_Vertical;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Recoil_Horizontal_Left;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Recoil_Horizontal_Right;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
