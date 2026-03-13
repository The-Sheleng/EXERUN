// © 2026 Andrii Shelenhivskyi. Licensed under Creative Commons Attribution-NonCommercial 4.0.

#include "AbilitySystem/AttributeSets/ExeRunAttributeSet.h"

#include "GameplayEffectExtension.h"

void UExeRunAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
	
	ClampAttribute(Attribute, NewValue);
}

void UExeRunAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	ClampAttribute(Attribute, NewValue);
}
