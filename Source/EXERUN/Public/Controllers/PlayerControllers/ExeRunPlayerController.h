// © 2026 Andrii Shelenhivskyi. Licensed under Creative Commons Attribution-NonCommercial 4.0.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerController.h"
#include "ExeRunPlayerController.generated.h"

class UNinjaInputManagerComponent;
class UExeRunAbilitySystemComponent;

/**
 * Player controller used in ExeRun project.
 *
 * Responsible for:
 * - Owning player input systems
 * - Initializing input manager component
 * - Serving as bridge between player and pawn input production
 * - Provides access to the Ability System Component of the owning character
 */
UCLASS()
class EXERUN_API AExeRunPlayerController : public APlayerController, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	/** Returns input manager responsible for processing player input */
	UNinjaInputManagerComponent* GetInputManagerComponent() const { return InputManagerComponent; }

	/** Returns the standard Ability System Component of the associated character */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	/** Returns the ExeRun-specific Ability System Component of the associated character */
	const UExeRunAbilitySystemComponent* GetExeRunAbilitySystemComponent() const;
	
	AExeRunPlayerController();


private:

	/** Centralized input manager handling NinjaInput system */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UNinjaInputManagerComponent> InputManagerComponent;
};
