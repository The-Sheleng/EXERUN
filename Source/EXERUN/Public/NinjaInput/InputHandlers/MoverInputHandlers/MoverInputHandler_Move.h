// © 2026 Andrii Shelenhivskyi. Licensed under Creative Commons Attribution-NonCommercial 4.0.

#pragma once

#include "CoreMinimal.h"
#include "MoverInputHandler.h"
#include "NinjaInput/Common/Structs/InputHandleCacheBase.h"
#include "MoverInputHandler_Move.generated.h"

/**
 * Cached move input data for Mover simulation.
 *
 * Stores last frame’s affirmative input, intended input vector,
 * and computed move velocity for prediction and replication.
 */
USTRUCT(BlueprintType)
struct FMoveInputHandleCache : public FInputHandleCacheBase
{
	GENERATED_BODY()

	/** Intended movement input from player/controller for current frame */
	FVector Intent = FVector::ZeroVector;

	/** Computed velocity based on MoveInputIntent and simulation */
	FVector Velocity = FVector::ZeroVector;
	
	/** Last confirmed directional input applied to character */
	FVector LastMoveInput = FVector::ZeroVector;
};

/**
 * Mover input handler responsible for character movement.
 *
 * Responsibilities:
 * - Reads player/controller input
 * - Consumes NavMoverComponent movement if available
 * - Updates MoveInput caches
 * - Determines final orientation intent for character
 */ 
UCLASS(meta = (DisplayName = "Mover: Move"))
class EXERUN_API UMoverInputHandler_Move : public UMoverInputHandler
{
	GENERATED_BODY()

public:

	UMoverInputHandler_Move();

	/**
	 * Produces mover input for the current frame.
	 *
	 * This method is the core of character movement input production.
	 * It reads input from cached MoveInputHandleCache, optional NavMoverComponent,
	 * applies rotation, chooses final movement intent, and determines the orientation intent.
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

	virtual void HandleTriggeredEvent_Implementation(
		UNinjaInputManagerComponent* Manager,
		const FInputActionValue& Value,
		const UInputAction* InputAction,
		float ElapsedTime
	) const override;

	virtual void HandleCompletedEvent_Implementation(
		UNinjaInputManagerComponent* Manager,
		const FInputActionValue& Value,
		const UInputAction* InputAction,
		float ElapsedTime
	) const override;


private:
	
	/** If true, movement is relative to the base we're standing on */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Move", meta=(AllowPrivateAccess="true"))
	bool bUseBaseRelativeMovement = true;

	/** If true, rotate character toward movement direction */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Move", 
		meta=(AllowPrivateAccess="true", InlineEditConditionToggle))
	bool bOrientRotationToMovement = true;

	/** Minimal movement magnitude required to update orientation intent */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Move", 
		meta=(AllowPrivateAccess="true", EditCondition="bOrientRotationToMovement"))
	float RotationMagMin = 1e-3f;
	
	/** If true, maintain last input orientation after movement stops */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Move", meta=(AllowPrivateAccess="true"))
	bool bMaintainLastInputOrientation = false;
};
