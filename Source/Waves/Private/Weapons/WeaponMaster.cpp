// Fill out your copyright notice in the Description page of Project Settings.

#include "Waves/Public/Weapons/WeaponMaster.h"
#include "Components/SkeletalMeshComponent.h"


// Sets default values
AWeaponMaster::AWeaponMaster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponModel = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponModel"));

	SetRootComponent(WeaponModel);

	WeaponModel->SetCastShadow(false);
}

// Called when the game starts or when spawned
void AWeaponMaster::BeginPlay()
{
	Super::BeginPlay();

	FireRate = 1 / FireRate;
	
}

// Called every frame
void AWeaponMaster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

