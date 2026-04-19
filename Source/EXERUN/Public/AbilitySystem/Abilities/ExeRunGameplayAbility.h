// © 2026 Andrii Shelenhivskyi. Licensed under Creative Commons Attribution-NonCommercial 4.0.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "ExeRunGameplayAbility.generated.h"

/** Base gameplay ability used in ExeRun project */
UCLASS()
class EXERUN_API UExeRunGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	
	UExeRunGameplayAbility();
	
	/**
	* void UGameplayAbility_Crouch::ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData)
		{
			Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
			
			if (!CommitAbility(Handle, ActorInfo, ActivationInfo) 
				|| !ensureAlways(ActorInfo && ActorInfo->AvatarActor.IsValid()))
			{
				CancelAbility(Handle, ActorInfo, ActivationInfo, true);
				return;
			}
			
			// Your Code
			
			EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		}

	 */
};
