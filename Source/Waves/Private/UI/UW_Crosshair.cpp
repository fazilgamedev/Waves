// Fill out your copyright notice in the Description page of Project Settings.

#include "Waves/Public/UI/UW_Crosshair.h"
#include "Waves/Public/Character/BaseCharacter.h"
#include "Animation/WidgetAnimation.h"

void UUW_Crosshair::NativeConstruct()
{
	Super::NativeConstruct();

	GetAnims();
}

void UUW_Crosshair::NativeTick(const FGeometry & Geometry, float InDeltaTime)
{
	Super::NativeTick(Geometry, InDeltaTime);
}

void UUW_Crosshair::GetAnims()
{
	UProperty* Prop = GetClass()->PropertyLink;
	while (Prop) {
		if (Prop->GetClass() == UObjectProperty::StaticClass()) {
			UObjectProperty* ObjectProp = Cast<UObjectProperty>(Prop);
			if (ObjectProp->PropertyClass == UWidgetAnimation::StaticClass()) {
				UObject* Object = ObjectProp->GetObjectPropertyValue_InContainer(this);
				UWidgetAnimation* Anim = Cast<UWidgetAnimation>(Object);
				if (Anim) {
					FString AnimName = Anim->GetName();
					if (AnimName.Contains(TEXT("CrosshairAnim"))) Crosshair = Anim;
					else if (AnimName.Contains(TEXT("FadeAnim"))) Fade = Anim;
				}
			}
		}
		Prop = Prop->PropertyLinkNext;
	}
}
