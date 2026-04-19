// © 2026 Andrii Shelenhivskyi. Licensed under Creative Commons Attribution-NonCommercial 4.0.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "ExeRunGameplayAbility.generated.h"

class UAbilityComponent;

/** Base gameplay ability used in ExeRun project */
UCLASS()
class EXERUN_API UExeRunGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	
	UExeRunGameplayAbility();
	
	virtual bool CommitAbility(
		const FGameplayAbilitySpecHandle Handle, 
		const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayAbilityActivationInfo ActivationInfo, 
		FGameplayTagContainer* OptionalRelevantTags = nullptr) override;
	
	virtual void CancelAbility(
		const FGameplayAbilitySpecHandle Handle, 
		const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayAbilityActivationInfo ActivationInfo, 
		bool bReplicateCancelAbility) override;


protected:

	virtual void PreActivate(
		const FGameplayAbilitySpecHandle Handle, 
		const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayAbilityActivationInfo ActivationInfo, 
		FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate, 
		const FGameplayEventData* TriggerEventData = nullptr) override;	
	
	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;
	
	virtual void EndAbility(
		const FGameplayAbilitySpecHandle Handle, 
		const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayAbilityActivationInfo ActivationInfo, 
		bool bReplicateEndAbility, 
		bool bWasCancelled) override;

	/** 
	 * Automatically commits the ability immediately before executing AbilityComponents.
	 * If commit fails, the ability will be canceled.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Execution")
	bool bAutoCommitAbility = false;
	
	/** If true, CancelAbility will be replicated when auto commit fails */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Execution", meta=(EditCondition="bAutoCommitAbility"))
	bool bReplicateCancelAutoCommitAbility = true;
	
	/** Automatically ends the ability immediately after all AbilityComponents finish execution */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Execution")
	bool bAutoEndAbility = false;

	/** If true, EndAbility will be replicated when auto end is triggered */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Execution", meta=(EditCondition="bAutoEndAbility"))
	bool bReplicateAutoEndAbility = true;
	
	/**
	 * Modular components that receive ability lifecycle events 
	 * (PreActivate, Activate, Commit, Cancel, End).
	 *
	 * Used to compose reusable ability behavior.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Execution", Instanced, meta=(ShowOnlyInnerProperties))
	TArray<TObjectPtr<UAbilityComponent>> AbilityComponents;
};
