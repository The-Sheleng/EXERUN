// © 2026 Andrii Shelenhivskyi. Licensed under Creative Commons Attribution-NonCommercial 4.0.

#pragma once

#include "NinjaInputHandler.h"
#include "ExeRunInputHandler_Move.generated.h"

/** ExeRun input handler responsible for character movement */ 
UCLASS(meta = (DisplayName = "ExeRun: Move"))
class EXERUN_API UExeRunInputHandler_Move : public UNinjaInputHandler
{
	GENERATED_BODY()

public:

	UExeRunInputHandler_Move();


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
};
