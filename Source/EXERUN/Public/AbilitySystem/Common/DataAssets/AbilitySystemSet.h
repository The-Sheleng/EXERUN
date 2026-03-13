// © 2026 Andrii Shelenhivskyi. Licensed under Creative Commons Attribution-NonCommercial 4.0.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AbilitySystemSet.generated.h"

class UExeRunAbilitySystemComponent;
class UExeRunGameplayEffect;
class UExeRunGameplayAbility;
class UExeRunAttributeSet;

/**
 * Data asset representing a grouped set of abilities, attributes, and effects.
 *
 * Each AbilitySystemSet is associated with a gameplay tag and can be granted
 * or removed as a unit from an AbilitySystemComponent.
 *
 * Responsibilities:
 * - Store references to attribute sets, abilities, and gameplay effects
 * - Apply or remove all associated components on a given AbilitySystemComponent
 * - Provide tag-based identification for dynamic management
 */
UCLASS()
class EXERUN_API UAbilitySystemSet : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	
	void GrantTo(UExeRunAbilitySystemComponent* AbilitySystemComponent) const;
	void TakeFrom(UExeRunAbilitySystemComponent* AbilitySystemComponent) const;

	
private:
	
	/** Tag used to identify this set for granting/removal */
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag AssociatedTag;

	UPROPERTY(EditDefaultsOnly, Category="Ability System Set")
	TArray<TSubclassOf<UExeRunAttributeSet>> AttributeSets;

	UPROPERTY(EditDefaultsOnly, Category="Ability System Set")
	TMap<TSubclassOf<UExeRunGameplayAbility>, int32> Abilities;

	UPROPERTY(EditDefaultsOnly, Category="Ability System Set")
	TMap<TSubclassOf<UExeRunGameplayEffect>, float> Effects;
	
	void GrantAttributeSetsTo(UExeRunAbilitySystemComponent* AbilitySystemComponent) const;
	void TakeAttributesFrom(UExeRunAbilitySystemComponent* AbilitySystemComponent) const;
	
	void GrantAbilitiesTo(UExeRunAbilitySystemComponent* AbilitySystemComponent) const;
	void TakeAbilitiesFrom(UExeRunAbilitySystemComponent* AbilitySystemComponent) const;
	
	void GrantEffectsTo(UExeRunAbilitySystemComponent* AbilitySystemComponent) const;
	void TakeEffectsFrom(UExeRunAbilitySystemComponent* AbilitySystemComponent) const;
};
