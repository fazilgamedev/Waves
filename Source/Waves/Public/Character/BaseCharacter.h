// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class USkeletalMeshComponent;
class UCameraComponent;
class AWeaponMaster;
class UArmsAnimInst;
class AHUD_Player;

UENUM(BlueprintType)
enum class EStatus : uint8 {
	Unarmed,
	Armed,
};

UCLASS()
class WAVES_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* Arms = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCameraComponent* Camera = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SprintSpeed = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float WalkSpeed = 187.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AWeaponMaster*> Weapons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 CurrentWeaponINT = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AWeaponMaster> AK47 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AWeaponMaster> G17 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EStatus CurrentStatus = EStatus::Unarmed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector WalkVector = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SideMove = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float FrontMove = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float H_Sensitivity = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float V_Sensitivity = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UArmsAnimInst* AnimInst = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bCanAttack = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bCanAim = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		APlayerController* PCREF = nullptr;

	UPROPERTY(VisibleAnywhere)
		AHUD_Player* HUDREF = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxHealth = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Health = MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsDead = false;

private:

	UPROPERTY()
		FHitResult HitResult;

	UPROPERTY()
		FTimerHandle FireHandle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCausor) override;

	UFUNCTION()
		void LookUp(float Value);

	UFUNCTION()
		void LookRight(float Value);

	UFUNCTION()
		void MoveFront(float Value);

	UFUNCTION()
		void MoveRight(float Value);

	UFUNCTION()
		AWeaponMaster* GetCurrentWeapon() const;

	UFUNCTION()
		void SetCurrentWeapon(AWeaponMaster* Weapon);

	UFUNCTION()
		void SetWeaponAtIndex(AWeaponMaster* Weapon, int32 INDEX);

	UFUNCTION()
		AWeaponMaster* GetWeaponAtIndex(int32 INDEX) const;

	UFUNCTION()
		void CreateWeapons();

	UFUNCTION()
		void Aim(float Value);

	UFUNCTION()
		void Fire();

	UFUNCTION()
		void Firing();

	UFUNCTION()
		void StopFire();

	UFUNCTION()
		void Recoil();

	UFUNCTION()
		void ChangeToSlot1();

	UFUNCTION()
		void ChangeToSlot2();

	UFUNCTION()
		void ChangeToUnarmed();

	UFUNCTION()
		void Sprint(float Value);
	
	
};
