// © 2026 Andrii Shelenhivskyi. Licensed under Creative Commons Attribution-NonCommercial 4.0.

#include "AbilitySystem/Common/DataAssets/AbilitySystemSet.h"

#include "AbilitySystem/AttributeSets/ExeRunAttributeSet.h"
#include "AbilitySystem/Components/ExeRunAbilitySystemComponent.h"
#include "AbilitySystem/Effects/ExeRunGameplayEffect.h"
#include "AbilitySystem/Abilities/ExeRunGameplayAbility.h"

void UAbilitySystemSet::GrantTo(UExeRunAbilitySystemComponent* AbilitySystemComponent) const
{
	if (!ensureAlways(IsValid(AbilitySystemComponent)) || !AbilitySystemComponent->IsOwnerActorAuthoritative()) return;

	GrantAttributeSetsTo(AbilitySystemComponent);
	GrantAbilitiesTo(AbilitySystemComponent);
	GrantEffectsTo(AbilitySystemComponent);
}

void UAbilitySystemSet::TakeFrom(UExeRunAbilitySystemComponent* AbilitySystemComponent) const
{
	if (!ensureAlways(IsValid(AbilitySystemComponent)) || !AbilitySystemComponent->IsOwnerActorAuthoritative()) return;

	TakeEffectsFrom(AbilitySystemComponent);
	TakeAbilitiesFrom(AbilitySystemComponent);
	TakeAttributesFrom(AbilitySystemComponent);
}

void UAbilitySystemSet::GrantAttributeSetsTo(UExeRunAbilitySystemComponent* AbilitySystemComponent) const
{
	if (!ensureAlways(IsValid(AbilitySystemComponent)) || !AbilitySystemComponent->IsOwnerActorAuthoritative()) return;
	
	for (const auto& AttributeSet : AttributeSets)
	{
		UExeRunAttributeSet* NewAttributeSet = NewObject<UExeRunAttributeSet>(
			AbilitySystemComponent->GetOwner(), 
			AttributeSet);
	
		AbilitySystemComponent->GrantAttributeSetByTag(AssociatedTag, NewAttributeSet);
	}
}

void UAbilitySystemSet::TakeAttributesFrom(UExeRunAbilitySystemComponent* AbilitySystemComponent) const
{
	if (!ensureAlways(IsValid(AbilitySystemComponent)) || !AbilitySystemComponent->IsOwnerActorAuthoritative())
	{
		AbilitySystemComponent->RemoveAttributeSetsByTag(AssociatedTag);	
	}
}

void UAbilitySystemSet::GrantAbilitiesTo(UExeRunAbilitySystemComponent* AbilitySystemComponent) const
{
	if (!ensureAlways(IsValid(AbilitySystemComponent)) || !AbilitySystemComponent->IsOwnerActorAuthoritative()) return;

	for (const auto& Ability : Abilities)
	{
		FGameplayAbilitySpec AbilitySpec(Ability.Key, Ability.Value);
		
		AbilitySystemComponent->GrantAbilitySpecByTag(AssociatedTag, AbilitySpec);
	}
}

void UAbilitySystemSet::TakeAbilitiesFrom(UExeRunAbilitySystemComponent* AbilitySystemComponent) const
{
	if (!ensureAlways(IsValid(AbilitySystemComponent)) || !AbilitySystemComponent->IsOwnerActorAuthoritative())
	{
		AbilitySystemComponent->RemoveAbilitiesByTag(AssociatedTag);
	}
}

void UAbilitySystemSet::GrantEffectsTo(UExeRunAbilitySystemComponent* AbilitySystemComponent) const
{
	if (!ensureAlways(IsValid(AbilitySystemComponent)) || !AbilitySystemComponent->IsOwnerActorAuthoritative()) return;

	for (const auto& EffectToGrant : Effects)
	{
		FGameplayEffectSpec EffectSpec(
			EffectToGrant.Key.GetDefaultObject(), 
			AbilitySystemComponent->MakeEffectContext(), 
			EffectToGrant.Value);

		AbilitySystemComponent->GrantEffectSpecByTag(AssociatedTag, EffectSpec);
	}
}

void UAbilitySystemSet::TakeEffectsFrom(UExeRunAbilitySystemComponent* AbilitySystemComponent) const
{
	if (!ensureAlways(IsValid(AbilitySystemComponent)) || !AbilitySystemComponent->IsOwnerActorAuthoritative())
	{
		AbilitySystemComponent->RemoveEffectsByTag(AssociatedTag);
	}
}
