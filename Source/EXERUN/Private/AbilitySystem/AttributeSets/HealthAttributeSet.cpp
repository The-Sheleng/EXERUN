// © 2026 Andrii Shelenhivskyi. Licensed under Creative Commons Attribution-NonCommercial 4.0.

#include "AbilitySystem/AttributeSets/HealthAttributeSet.h"

#include "AbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"

void UHealthAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Health, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxHealth, COND_None, REPNOTIFY_Always)
}

void UHealthAttributeSet::ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::ClampAttribute(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		/** Do not allow the Health to drop below 0 and above MaxHealth */
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	else if (Attribute == GetMaxHealthAttribute())
	{
		/** Do not allow MaxHealth to drop below 1 */
		NewValue = FMath::Max(NewValue, 1.f);
	}
}

void UHealthAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
	
	UAbilitySystemComponent* OwningAbilitySystemComponent = GetOwningAbilitySystemComponent();

	/** Make sure current health is not greater than the new max health */
	if (Attribute == GetMaxHealthAttribute() && GetHealth() > NewValue)
	{
		OwningAbilitySystemComponent->ApplyModToAttribute(GetHealthAttribute(), EGameplayModOp::Override, NewValue);
	}
}

void UHealthAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Health, OldValue);
}

void UHealthAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxHealth, OldValue);
}
