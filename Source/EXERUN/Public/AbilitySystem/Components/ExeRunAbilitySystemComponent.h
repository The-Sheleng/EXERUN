// © 2026 Andrii Shelenhivskyi. Licensed under Creative Commons Attribution-NonCommercial 4.0.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "ExeRunAbilitySystemComponent.generated.h"

class UAbilitySystemSet;
class UExeRunAttributeSet;

/**
 * Stores granted attributes, abilities, and effects associated with a gameplay tag.
 * Used internally by UExeRunAbilitySystemComponent to track what has been applied for a given tag.
 */
USTRUCT()
struct FAbilitySystemSet_Data
{
	GENERATED_BODY()

	TArray<TWeakObjectPtr<UExeRunAttributeSet>> GrantedAttributeSets;
	TArray<FGameplayAbilitySpecHandle> GrantedAbilities;
	TArray<FActiveGameplayEffectHandle> GrantedEffects;
};

/**
 * ExeRun-specific Ability System Component.
 *
 * Extends UAbilitySystemComponent to support grouping of attributes, abilities,
 * and effects via tags (AbilitySystemSets). Provides methods to grant or remove
 * these grouped sets dynamically.
 *
 * Responsibilities:
 * - Grant or remove attribute sets, abilities, and effects by tag
 * - Maintain internal mapping of granted sets for safe removal
 * - Initialize default AbilitySystemSets on actor spawn
 */
UCLASS()
class EXERUN_API UExeRunAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:

	void GrantAttributeSetByTag(const FGameplayTag& Tag, UExeRunAttributeSet* AttributeSet);
	void RemoveAttributeSetsByTag(const FGameplayTag& AssociatedTag);

	void GrantAbilitySpecByTag(const FGameplayTag& Tag, const FGameplayAbilitySpec& AbilitySpec);
	void RemoveAbilitiesByTag(const FGameplayTag& AssociatedTag);

	void GrantEffectSpecByTag(const FGameplayTag& Tag, const FGameplayEffectSpec& EffectSpec);
	void RemoveEffectsByTag(const FGameplayTag& AssociatedTag);
	
	virtual void InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor) override;


private:
	
	/** Default ability system sets applied on actor initialization */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TArray<TObjectPtr<UAbilitySystemSet>> AbilitySystemSets;
	
	/** Internal mapping of granted sets, abilities, and effects by tag */
	TMap<FGameplayTag, FAbilitySystemSet_Data> AbilitySystemSetDataByTag;
};
