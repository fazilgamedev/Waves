// Fill out your copyright notice in the Description page of Project Settings.

#include "Waves/Public/Camera/FireCamShake.h"

UFireCamShake::UFireCamShake()
{
	OscillationDuration = 0.25f;
	OscillationBlendInTime = 0.05f;
	OscillationBlendOutTime = 0.05f;

	RotOscillation.Roll.Amplitude = FMath::FloatSelect(FMath::RandBool(), -0.5f, 0.5f);
	RotOscillation.Roll.Frequency = 60.f;
}


