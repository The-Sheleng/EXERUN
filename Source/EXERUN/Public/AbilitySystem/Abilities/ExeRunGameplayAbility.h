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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components")
	bool bAutoCommitAbility = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components", meta=(EditCondition="bAutoCommitAbility"))
	bool bReplicateCancelAutoCommitAbility = true;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components")
	bool bAutoEndAbility = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components", meta=(EditCondition="bAutoEndAbility"))
	bool bReplicateAutoEndAbility = true;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components", Instanced, meta=(ShowOnlyInnerProperties))
	TArray<TObjectPtr<UAbilityComponent>> AbilityComponents;
};
