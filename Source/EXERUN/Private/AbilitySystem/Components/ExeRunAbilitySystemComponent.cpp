// © 2026 Andrii Shelenhivskyi. Licensed under Creative Commons Attribution-NonCommercial 4.0.

#include "AbilitySystem/Components/ExeRunAbilitySystemComponent.h"

#include "AbilitySystem/AttributeSets/ExeRunAttributeSet.h"
#include "AbilitySystem/Common/DataAssets/AbilitySystemSet.h"

void UExeRunAbilitySystemComponent::GrantAttributeSetByTag(const FGameplayTag& Tag, UExeRunAttributeSet* AttributeSet)
{
	FAbilitySystemSet_Data& AbilitySystemSetData = AbilitySystemSetDataByTag.FindOrAdd(Tag);

	if (ensureAlways(!AbilitySystemSetData.GrantedAttributeSets.Contains(AttributeSet)))
	{
		AddSpawnedAttribute(AttributeSet);
		AbilitySystemSetData.GrantedAttributeSets.Add(AttributeSet);
	}
}

void UExeRunAbilitySystemComponent::RemoveAttributeSetsByTag(const FGameplayTag& AssociatedTag)
{
	FAbilitySystemSet_Data* AbilitySystemSetData = AbilitySystemSetDataByTag.Find(AssociatedTag);

	if (!AbilitySystemSetData) return;
		
	for (TWeakObjectPtr SetToRemove : AbilitySystemSetData->GrantedAttributeSets)
	{
		if (SetToRemove.IsValid()) RemoveSpawnedAttribute(SetToRemove.Get());
	}
		
	AbilitySystemSetData->GrantedAttributeSets.Empty();
}

void UExeRunAbilitySystemComponent::GrantAbilitySpecByTag(
	const FGameplayTag& Tag, 
	const FGameplayAbilitySpec& AbilitySpec)
{
	FAbilitySystemSet_Data& AbilitySystemSetData = AbilitySystemSetDataByTag.FindOrAdd(Tag);
		
	AbilitySystemSetData.GrantedAbilities.Add(GiveAbility(AbilitySpec));
}

void UExeRunAbilitySystemComponent::RemoveAbilitiesByTag(const FGameplayTag& AssociatedTag)
{
	FAbilitySystemSet_Data* AbilitySystemSetData = AbilitySystemSetDataByTag.Find(AssociatedTag);

	if (!AbilitySystemSetData) return;
		
	for (FGameplayAbilitySpecHandle& SetToRemove : AbilitySystemSetData->GrantedAbilities)
	{
		if (SetToRemove.IsValid()) ClearAbility(SetToRemove);
	}
		
	AbilitySystemSetData->GrantedAbilities.Empty();
}

void UExeRunAbilitySystemComponent::GrantEffectSpecByTag(const FGameplayTag& Tag, const FGameplayEffectSpec& EffectSpec)
{
	FAbilitySystemSet_Data& AbilitySystemSetData = AbilitySystemSetDataByTag.FindOrAdd(Tag);
		
	AbilitySystemSetData.GrantedEffects.Add(ApplyGameplayEffectSpecToSelf(EffectSpec));
}

void UExeRunAbilitySystemComponent::RemoveEffectsByTag(const FGameplayTag& AssociatedTag)
{
	FAbilitySystemSet_Data* AbilitySystemSetData = AbilitySystemSetDataByTag.Find(AssociatedTag);

	if (!AbilitySystemSetData) return;

	for (FActiveGameplayEffectHandle& SetToRemove : AbilitySystemSetData->GrantedEffects)
	{
		if (SetToRemove.IsValid()) RemoveActiveGameplayEffect(SetToRemove);
	}
		
	AbilitySystemSetData->GrantedEffects.Empty();
}

void UExeRunAbilitySystemComponent::InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor)
{
	Super::InitAbilityActorInfo(InOwnerActor, InAvatarActor);
	
	for (const UAbilitySystemSet* AbilitySystemSet : AbilitySystemSets)
	{
		if (ensureAlways(IsValid(AbilitySystemSet)))
		{
			AbilitySystemSet->GrantTo(this);
		}
	}
}
