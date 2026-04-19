// © 2026 Andrii Shelenhivskyi. Licensed under Creative Commons Attribution-NonCommercial 4.0.

#pragma once
#include "NinjaInputHandler.h"

#include "ExeRunInputHandler_Jump.generated.h"

/** ExeRun input handler responsible for jump actions */
UCLASS(meta = (DisplayName = "ExeRun: Jump"))
class EXERUN_API UExeRunInputHandler_Jump : public UNinjaInputHandler
{
	GENERATED_BODY()

public:

	UExeRunInputHandler_Jump();

	
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
