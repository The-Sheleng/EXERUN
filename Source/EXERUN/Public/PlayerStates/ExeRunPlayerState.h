// © 2026 Andrii Shelenhivskyi. Licensed under Creative Commons Attribution-NonCommercial 4.0.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "ExeRunPlayerState.generated.h"

class UExeRunAbilitySystemComponent;

/**
 * Player state used in ExeRun project.
 *
 * Responsibilities:
 * - Provides access to the Ability System Component of the owning character
 */
UCLASS()
class EXERUN_API AExeRunPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	/** Returns the standard Ability System Component of the associated character */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	/** Returns the ExeRun-specific Ability System Component of the associated character */
	const UExeRunAbilitySystemComponent* GetExeRunAbilitySystemComponent() const;
};
