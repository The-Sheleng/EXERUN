// © 2026 Andrii Shelenhivskyi. Licensed under Creative Commons Attribution-NonCommercial 4.0.

#include "NinjaInput/InputHandlers/MoverInputHandlers/MoverInputHandler_Jump.h"

#include "NinjaInput/Components/ExeRunInputManagerComponent.h"
#include "DefaultMovementSet/NavMoverComponent.h"
#include "Pawns/ExeRunCharacter.h"

UMoverInputHandler_Jump::UMoverInputHandler_Jump()
{
	TriggerEvents.Add(ETriggerEvent::Started);
	TriggerEvents.Add(ETriggerEvent::Completed);
}
 
void UMoverInputHandler_Jump::HandleStartedEvent_Implementation(
	UNinjaInputManagerComponent* Manager,
	const FInputActionValue& Value, 
	const UInputAction* InputAction) const
{
	UExeRunInputManagerComponent* CastedManager = Cast<UExeRunInputManagerComponent>(Manager);
	if (!ensureAlways(IsValid(CastedManager))) return;
		
	FJumpInputHandleCache& JumpCache = CastedManager->FindOrAddInputHandleCacheByType<FJumpInputHandleCache>();
	
	JumpCache.bIsJustPressed = !JumpCache.bIsPressed;
	JumpCache.bIsPressed = true;
}

void UMoverInputHandler_Jump::HandleCompletedEvent_Implementation(UNinjaInputManagerComponent* Manager,
	const FInputActionValue& Value, const UInputAction* InputAction, float ElapsedTime) const
{
	UExeRunInputManagerComponent* CastedManager = Cast<UExeRunInputManagerComponent>(Manager);
	if (!ensureAlways(IsValid(CastedManager))) return;
		
	FJumpInputHandleCache& JumpCache = CastedManager->FindOrAddInputHandleCacheByType<FJumpInputHandleCache>();
	
	JumpCache.bIsJustPressed = false;
	JumpCache.bIsPressed = false;
}

void UMoverInputHandler_Jump::ProduceInput(
	UExeRunInputManagerComponent* Manager,
	int32 SimTimeMs,
	FMoverInputCmdContext& InputCmdResult)
{
	if (!ensureAlways(IsValid(Manager))) return;
		
	const APawn* Pawn = Manager->GetPawn();
	if (!ensureAlways(IsValid(Pawn))) return;
		
	FCharacterDefaultInputs& CharacterInputs =
		InputCmdResult.InputCollection.FindOrAddMutableDataByType<FCharacterDefaultInputs>();

	FJumpInputHandleCache& JumpInputCache = Manager->FindOrAddInputHandleCacheByType<FJumpInputHandleCache>();
	
	/** We pass the button state to the input structure for Mover */
	CharacterInputs.bIsJumpPressed = JumpInputCache.bIsPressed;
	CharacterInputs.bIsJumpJustPressed = JumpInputCache.bIsJustPressed;
	
	/** After processing, reset the "just pressed" flag */
	JumpInputCache.bIsJustPressed = false;
}
