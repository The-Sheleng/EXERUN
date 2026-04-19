// © 2026 Andrii Shelenhivskyi. Licensed under Creative Commons Attribution-NonCommercial 4.0.

#include "AbilitySystem/Abilities/ExeRunGameplayAbility.h"

#include "AbilitySystem/AbilityComponents/AbilityComponent.h"

UExeRunGameplayAbility::UExeRunGameplayAbility()
{
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::ReplicateNo;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::ClientOrServer;
}

bool UExeRunGameplayAbility::CommitAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo,
	FGameplayTagContainer* OptionalRelevantTags)
{
	const bool Result =  Super::CommitAbility(Handle, ActorInfo, ActivationInfo, OptionalRelevantTags);
	
	for (UAbilityComponent* Component : AbilityComponents)
	{
		Component->OnCommitAbility(Handle, ActorInfo, ActivationInfo, OptionalRelevantTags);
	}
	
	return Result;
}

void UExeRunGameplayAbility::PreActivate(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo,
	FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate, 
	const FGameplayEventData* TriggerEventData)
{
	Super::PreActivate(Handle, ActorInfo, ActivationInfo, OnGameplayAbilityEndedDelegate, TriggerEventData);

	for (UAbilityComponent* Component : AbilityComponents)
	{
		Component->OnPreActivate(Handle, ActorInfo, ActivationInfo, OnGameplayAbilityEndedDelegate, TriggerEventData);
	}
}

void UExeRunGameplayAbility::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	if (bAutoCommitAbility && !CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAutoCommitAbility);
		return;
	}
	
	if (bAutoCommitAbility || !CommitCheck(Handle, ActorInfo, ActivationInfo))
	{
		for (UAbilityComponent* Component : AbilityComponents)
		{
			Component->OnActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
		}
	}
	
	if (bAutoEndAbility)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateAutoEndAbility, false);
	}
}

void UExeRunGameplayAbility::CancelAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateCancelAbility)
{
	for (UAbilityComponent* Component : AbilityComponents)
	{
		Component->OnCancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
	}
	
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UExeRunGameplayAbility::EndAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	for (UAbilityComponent* Component : AbilityComponents)
	{
		Component->OnEndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	}
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

}
