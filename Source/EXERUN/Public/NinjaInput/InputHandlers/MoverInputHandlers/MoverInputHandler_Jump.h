// © 2026 Andrii Shelenhivskyi. Licensed under Creative Commons Attribution-NonCommercial 4.0.

#pragma once

#include "CoreMinimal.h"
#include "MoverInputHandler.h"
#include "NinjaInput/Common/Structs/InputHandleCacheBase.h"
#include "MoverInputHandler_Jump.generated.h"

/**
 * Cached jump input data for Mover simulation.
 *
 * Tracks jump button state for the current frame, including:
 * - Whether the button was just pressed
 * - Whether the button is currently held
 */
USTRUCT(BlueprintType)
struct FJumpInputHandleCache : public FInputHandleCacheBase
{
	GENERATED_BODY()

	/** True if the jump button was just pressed this frame */
	bool bIsJustPressed = false;
	
	/** True if the jump button is currently held */
	bool bIsPressed = false;
};

/**
 * Mover input handler responsible for jump actions.
 *
 * Responsibilities:
 * - Reads jump input from player/controller
 * - Updates cached jump input states
 * - Produces jump input for the Mover simulation
 */
UCLASS(meta = (DisplayName = "Mover: Jump"))
class EXERUN_API UMoverInputHandler_Jump : public UMoverInputHandler
{
	GENERATED_BODY()

public:

	UMoverInputHandler_Jump();

	/**
	 * Produces mover input for jump actions for the current frame.
	 *
	 * Reads cached jump input states (pressed/just pressed) and updates
	 * the FCharacterDefaultInputs structure for the simulation.
	 *
	 * @param Manager ExeRun input manager owning this handler
	 * @param SimTimeMs Current simulation time in milliseconds
	 * @param InputCmdResult Output mover input context
	 */
	virtual void ProduceInput(
		UExeRunInputManagerComponent* Manager, 
		int32 SimTimeMs, 
		FMoverInputCmdContext& InputCmdResult
	) override;

protected:

	virtual void HandleStartedEvent_Implementation(
		UNinjaInputManagerComponent* Manager, 
		const FInputActionValue& Value,
		const UInputAction* InputAction
	) const override;

	virtual void HandleCompletedEvent_Implementation(
		UNinjaInputManagerComponent* Manager,
		const FInputActionValue& Value,
		const UInputAction* InputAction,
		float ElapsedTime
	) const override;
};
