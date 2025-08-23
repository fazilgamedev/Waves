// Fill out your copyright notice in the Description page of Project Settings.

#include "Waves/Public/Character/BaseCharacter.h"
#include "Waves/Public/Weapons/WeaponMaster.h"
#include "Waves/Public/Character/Animations/ArmsAnimInst.h"
#include "Waves/Public/Camera/FireCamShake.h"
#include "Waves/Public/UI/HUD_Player.h"
#include "Waves/Public/UI/UW_Crosshair.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	Camera->SetupAttachment(RootComponent);

	Arms = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Arms"));

	Arms->SetupAttachment(Camera);

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	AnimInst = Cast<UArmsAnimInst>(Arms->GetAnimInstance());

	PCREF = Cast<APlayerController>(GetController());

	HUDREF = Cast<AHUD_Player>(PCREF->GetHUD());

	Weapons.Init(nullptr, 2);
	
	CurrentStatus = EStatus::Unarmed;

	CreateWeapons();

}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetCurrentWeapon()) {
		if (bCanAttack) {
			Recoil();
		}
	}
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABaseCharacter::Jump);
	PlayerInputComponent->BindAction("Firing", IE_Pressed, this, &ABaseCharacter::Firing);
	PlayerInputComponent->BindAction("Firing", IE_Released, this, &ABaseCharacter::StopFire);
	PlayerInputComponent->BindAction("Slot1", IE_Pressed, this, &ABaseCharacter::ChangeToSlot1);
	PlayerInputComponent->BindAction("Slot2", IE_Pressed, this, &ABaseCharacter::ChangeToSlot2);
	PlayerInputComponent->BindAction("Unarmed", IE_Pressed, this, &ABaseCharacter::ChangeToUnarmed);
	PlayerInputComponent->BindAxis("LookUp", this, &ABaseCharacter::LookUp);
	PlayerInputComponent->BindAxis("LookRight", this, &ABaseCharacter::LookRight);
	PlayerInputComponent->BindAxis("MoveFront", this, &ABaseCharacter::MoveFront);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Aim", this, &ABaseCharacter::Aim);
	PlayerInputComponent->BindAxis("Sprint", this, &ABaseCharacter::Sprint);

}

float ABaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCausor)
{
	UE_LOG(LogTemp, Warning, TEXT("Hitt"));
	return 1.f;
}

void ABaseCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value * V_Sensitivity);
}

void ABaseCharacter::LookRight(float Value)
{
	AddControllerYawInput(Value * H_Sensitivity);
}

void ABaseCharacter::MoveFront(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
	FrontMove = AnimInst->AimAlpha > .5f ? Value * .3f : Value;
}

void ABaseCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
	SideMove = Value;
}

AWeaponMaster * ABaseCharacter::GetCurrentWeapon() const
{
	return Weapons.IsValidIndex(CurrentWeaponINT) ? Weapons[CurrentWeaponINT] : nullptr;
}

void ABaseCharacter::SetCurrentWeapon(AWeaponMaster * Weapon)
{
	Weapons[CurrentWeaponINT] = Weapon;
}

void ABaseCharacter::SetWeaponAtIndex(AWeaponMaster* Weapon, int32 INDEX)
{
	Weapons[INDEX] = Weapon;
}

AWeaponMaster * ABaseCharacter::GetWeaponAtIndex(int32 INDEX) const
{
	return Weapons.IsValidIndex(INDEX) ? Weapons[INDEX] : nullptr;
}

void ABaseCharacter::CreateWeapons()
{
	FActorSpawnParameters SpawnParams;
	SetWeaponAtIndex(GetWorld()->SpawnActor<AWeaponMaster>(AK47, GetActorLocation(), GetActorRotation(), SpawnParams), 0);
	SetWeaponAtIndex(GetWorld()->SpawnActor<AWeaponMaster>(G17, GetActorLocation(), GetActorRotation(), SpawnParams), 1);
	GetWeaponAtIndex(0)->WeaponModel->SetVisibility(false);
	GetWeaponAtIndex(1)->WeaponModel->SetVisibility(false);
	GetWeaponAtIndex(0)->WeaponModel->AttachToComponent(Arms, FAttachmentTransformRules::SnapToTargetIncludingScale, GetWeaponAtIndex(0)->SocketToAttach);
	GetWeaponAtIndex(1)->WeaponModel->AttachToComponent(Arms, FAttachmentTransformRules::SnapToTargetIncludingScale, GetWeaponAtIndex(1)->SocketToAttach);
}

void ABaseCharacter::Aim(float Value)
{
	if (!GetCurrentWeapon()) return;
	AnimInst->AimAlpha = UKismetMathLibrary::FInterpTo(AnimInst->AimAlpha, Value, GetWorld()->GetDeltaSeconds(), 10.f);
	Camera->SetFieldOfView(UKismetMathLibrary::FInterpTo(Camera->FieldOfView, UKismetMathLibrary::Lerp(120.f, GetCurrentWeapon()->ADSFOV, Value), GetWorld()->GetDeltaSeconds(), 10.f));
	if (Value < .5f) {
		bCanAim = true;
		HUDREF->CrosshairWidget->PlayAnimation(HUDREF->CrosshairWidget->Fade, 0.f, 1, EUMGSequencePlayMode::Forward, 1.f);
	}
	else {
		bCanAim = false;
		HUDREF->CrosshairWidget->PlayAnimation(HUDREF->CrosshairWidget->Fade, 0.f, 1, EUMGSequencePlayMode::Reverse, 1.f);
	}
}

void ABaseCharacter::Fire()
{
	if (bCanAttack && GetCurrentWeapon() && CurrentStatus == EStatus::Armed) {
		FVector Start = GetCurrentWeapon()->WeaponModel->GetSocketLocation("Muzzle");
		FVector End = GetCurrentWeapon()->WeaponModel->GetSocketLocation("Muzzle") + Camera->GetForwardVector() * GetCurrentWeapon()->Range;
		AnimInst->Firing();
		if (GetCurrentWeapon()->FireSeq) GetCurrentWeapon()->WeaponModel->PlayAnimation(GetCurrentWeapon()->FireSeq, false);
		PCREF->ClientPlayCameraShake(UFireCamShake::StaticClass(), 1.3f);
		if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility)) {
			if (HitResult.GetActor()) {
				if (HitResult.GetActor()->Tags.Num() > 0) {
					if (HitResult.GetActor()->ActorHasTag("Metal")) {
						UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), GetCurrentWeapon()->HitEffect[0], HitResult.Location, HitResult.ImpactNormal.Rotation());
					}
					else if (HitResult.GetActor()->ActorHasTag("Enemy")) {
						UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), GetCurrentWeapon()->HitEffect[1], HitResult.Location, HitResult.ImpactNormal.Rotation());
						UGameplayStatics::ApplyPointDamage(HitResult.GetActor(), GetCurrentWeapon()->Damage, (End - Start).GetSafeNormal(), HitResult, PCREF, this, UDamageType::StaticClass());
					}
					else if (HitResult.GetActor()->ActorHasTag("Wood")) {
						UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), GetCurrentWeapon()->HitEffect[2], HitResult.Location, HitResult.ImpactNormal.Rotation());
					}
					else if (HitResult.GetActor()->ActorHasTag("Ground")) {
						UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), GetCurrentWeapon()->HitEffect[3], HitResult.Location, HitResult.ImpactNormal.Rotation());
					}
				}
			}
		}
	}
}

void ABaseCharacter::Firing()
{
	if (!(GetCurrentWeapon() && CurrentStatus == EStatus::Armed)) return;
	bCanAttack = true;
	HUDREF->CrosshairWidget->PlayAnimation(HUDREF->CrosshairWidget->Crosshair, 0.f, 1, EUMGSequencePlayMode::Forward, 1.f);
	Fire();
	GetWorldTimerManager().SetTimer(FireHandle, this, &ABaseCharacter::Fire, GetCurrentWeapon()->FireRate, true);
}

void ABaseCharacter::StopFire()
{
	if (!(GetCurrentWeapon() && CurrentStatus == EStatus::Armed)) return;
	bCanAttack = false;
	HUDREF->CrosshairWidget->PlayAnimation(HUDREF->CrosshairWidget->Crosshair, 0.f, 1, EUMGSequencePlayMode::Reverse, 1.f);
	GetWorldTimerManager().ClearTimer(FireHandle);
}

void ABaseCharacter::Recoil()
{
	AddControllerPitchInput(GetCurrentWeapon()->Recoil_Vertical);
	AddControllerYawInput(GetCurrentWeapon()->Recoil_Horizontal_Left);
	AddControllerYawInput(GetCurrentWeapon()->Recoil_Horizontal_Right);
}

void ABaseCharacter::ChangeToSlot1()
{
	if (CurrentWeaponINT != 0 || CurrentStatus == EStatus::Unarmed) {
		bCanAttack = false;
		GetWeaponAtIndex(0)->WeaponModel->SetVisibility(true);
		GetWeaponAtIndex(1)->WeaponModel->SetVisibility(false);
		CurrentStatus = EStatus::Armed;
		CurrentWeaponINT = 0;
	}
}

void ABaseCharacter::ChangeToSlot2()
{
	if (CurrentWeaponINT != 1 || CurrentStatus == EStatus::Unarmed) {
		bCanAttack = false;
		GetWeaponAtIndex(1)->WeaponModel->SetVisibility(true);
		GetWeaponAtIndex(0)->WeaponModel->SetVisibility(false);
		CurrentStatus = EStatus::Armed;
		CurrentWeaponINT = 1;
	}
}

void ABaseCharacter::ChangeToUnarmed()
{
	if (CurrentWeaponINT != -1 || CurrentStatus != EStatus::Unarmed) {
		bCanAttack = false;
		GetWeaponAtIndex(1)->WeaponModel->SetVisibility(false);
		GetWeaponAtIndex(0)->WeaponModel->SetVisibility(false);
		CurrentStatus = EStatus::Unarmed;
		CurrentWeaponINT = -1;
	}
}

void ABaseCharacter::Sprint(float Value)
{
	GetCharacterMovement()->MaxWalkSpeed = Value > .5f ? SprintSpeed : WalkSpeed;
}


