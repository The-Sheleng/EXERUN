// © 2026 Andrii Shelenhivskyi. Licensed under Creative Commons Attribution-NonCommercial 4.0.

#pragma once

#include "CoreMinimal.h"
#include "NinjaInputHandler.h"
#include "MoverInputHandler.generated.h"

class UExeRunInputManagerComponent;
struct FMoverInputCmdContext;

/**
 * Abstract base class for all mover input handlers in ExeRun.
 *
 * Responsible for producing movement input for Mover system
 * every simulation frame.
 */
UCLASS(Abstract)
class EXERUN_API UMoverInputHandler : public UNinjaInputHandler
{
	GENERATED_BODY()

public:

	/**
	 * Produces input for the given manager and simulation context.
	 *
	 * @param Manager The owning ExeRun input manager
	 * @param SimTimeMs Current simulation time in milliseconds
	 * @param InputCmdResult Output context for mover input commands
	 */
	virtual void ProduceInput(
		UExeRunInputManagerComponent* Manager, 
		int32 SimTimeMs, 
		FMoverInputCmdContext& InputCmdResult
	) PURE_VIRTUAL();
};