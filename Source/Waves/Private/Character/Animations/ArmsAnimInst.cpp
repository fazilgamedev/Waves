// Fill out your copyright notice in the Description page of Project Settings.

#include "Waves/Public/Character/Animations/ArmsAnimInst.h"
#include "Waves/Public/Character/BaseCharacter.h"
#include "Waves/Public/Weapons/WeaponMaster.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UArmsAnimInst::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	CharacterREF = Cast<ABaseCharacter>(TryGetPawnOwner());
	if (!CharacterREF) return;
	else OldRotation = CharacterREF->GetControlRotation();
}

void UArmsAnimInst::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (!CharacterREF) return;

	Speed = CharacterREF->GetVelocity().Size2D();

	Direction = CalculateDirection(CharacterREF->GetVelocity(), CharacterREF->GetActorRotation());

	CurrentWeapon = CharacterREF->GetCurrentWeapon();

	SideRotation(CharacterREF->SideMove, DeltaTime);
	FrontRotation(CharacterREF->FrontMove, DeltaTime);

	WalkAnim(DeltaTime);

	HandSway(DeltaTime);


	if (CurrentWeapon && CharacterREF->CurrentStatus == EStatus::Armed) {

		LHIKAlpha = 1.f;

		SetSightTransform();

		SetRelativeHandTransform();

		SetLHIKTransform();

		if (!RecoilTransform.Equals(FTransform()) || !RecoilResetTransform.Equals(FTransform())) {

			InterpResetRecoil(DeltaTime);

			InterpRecoil(DeltaTime);

		}
	}
	else {

		LHIKAlpha = 0.f;
		AimAlpha = 0.f;
	}
}

FTransform UArmsAnimInst::MakeRelativeTransform(FTransform A, FTransform RelativeTo)
{
	return UKismetMathLibrary::ComposeTransforms(A, UKismetMathLibrary::InvertTransform(RelativeTo));
}

void UArmsAnimInst::SetSightTransform()
{
	FTransform Temp = MakeRelativeTransform(CharacterREF->Camera->GetComponentTransform(), CharacterREF->Arms->GetComponentTransform());
	SightTransform = FTransform(Temp.GetRotation(), Temp.GetRotation().GetForwardVector() * CurrentWeapon->AimOffset + Temp.GetLocation());
}

void UArmsAnimInst::SetRelativeHandTransform()
{
	RelativeHandTransform = MakeRelativeTransform(CurrentWeapon->WeaponModel->GetSocketTransform(FName("S_Aim"), ERelativeTransformSpace::RTS_World), CharacterREF->Arms->GetSocketTransform(FName("R_wrist"), ERelativeTransformSpace::RTS_World));
}

void UArmsAnimInst::SetLHIKTransform()
{
	LHIKTransform = MakeRelativeTransform(CurrentWeapon->WeaponModel->GetSocketTransform(FName("S_LHIK"), ERelativeTransformSpace::RTS_World), CharacterREF->Arms->GetSocketTransform(FName("R_wrist"), ERelativeTransformSpace::RTS_World));
}

void UArmsAnimInst::WalkAnim(float DeltaTime)
{
	SwayVector = UKismetMathLibrary::VInterpTo(SwayVector, CharacterREF->WalkVector, DeltaTime, 10.f);
}

void UArmsAnimInst::HandSway(float DeltaTime)
{
	FRotator CurrentRotation = CharacterREF->GetControlRotation();
	// Clamp if needed
	TurnRotation = UKismetMathLibrary::RInterpTo(TurnRotation, CurrentRotation - OldRotation, DeltaTime, 9.f);
	TurnRotation.Roll = TurnRotation.Pitch * -1.f;
	TurnRotation.Yaw = FMath::Clamp(TurnRotation.Yaw, -9.f, 9.f);
	TurnRotation.Roll = FMath::Clamp(TurnRotation.Roll, -9.f, 9.f);
	TurnLocation.X = TurnRotation.Yaw / 18.f;
	TurnLocation.Z = TurnRotation.Roll / 18.f;
	OldRotation = CurrentRotation;
}

void UArmsAnimInst::SideRotation(float _SideMove, float DeltaTime)
{
	SideMove = UKismetMathLibrary::FInterpTo(SideMove, UKismetMathLibrary::MapRangeClamped(_SideMove, -1.f, 1.f, -6.f, 6.f), DeltaTime, 8.f);
}

void UArmsAnimInst::FrontRotation(float _FrontMove, float DeltaTime)
{
	FrontMove = UKismetMathLibrary::FInterpTo(FrontMove, UKismetMathLibrary::MapRangeClamped(_FrontMove, -1.f, 1.f, -6.f, 6.f), DeltaTime, 8.f);
}

void UArmsAnimInst::InterpRecoil(float DeltaTime)
{
	RecoilResetTransform = UKismetMathLibrary::TInterpTo(RecoilResetTransform, FTransform(), DeltaTime, 10.f);
}

void UArmsAnimInst::InterpResetRecoil(float DeltaTime)
{
	RecoilTransform = UKismetMathLibrary::TInterpTo(RecoilTransform, RecoilResetTransform, DeltaTime, 10.f);
}

void UArmsAnimInst::Firing()
{
	FVector RecoilLocation = RecoilResetTransform.GetLocation();
	RecoilLocation += FVector(FMath::RandRange(CurrentWeapon->RightRecoil * -1.f, CurrentWeapon->RightRecoil), FMath::RandRange(CurrentWeapon->FrontRecoil * -1.f - 1.f, CurrentWeapon->FrontRecoil * -1.f), FMath::RandRange(CurrentWeapon->UpRecoil * -1.f, CurrentWeapon->UpRecoil));
	FRotator RocoilRotation = RecoilResetTransform.GetRotation().Rotator();
	RocoilRotation += FRotator(FMath::RandRange(CurrentWeapon->HorizontalRecoil * -1.f, CurrentWeapon->HorizontalRecoil), FMath::RandRange(CurrentWeapon->SideRecoil * -1.f, CurrentWeapon->SideRecoil), FMath::RandRange(CurrentWeapon->VerticalRecoil * -1.f - 1.f, CurrentWeapon->VerticalRecoil * -1.f));
	RecoilResetTransform.SetRotation(RocoilRotation.Quaternion());
	RecoilResetTransform.SetLocation(RecoilLocation);
}

