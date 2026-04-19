// © 2026 Andrii Shelenhivskyi. Licensed under Creative Commons Attribution-NonCommercial 4.0.

#include "NinjaInput/InputHandlers/MoverInputHandlers/ExeRunInputHandler_Jump.h"

#include "Components/NinjaInputManagerComponent.h"
#include "Mover/Components/ExeRunMoverComponent.h"
#include "Mover/InputProducers/InputProducer_Character.h"
#include "Pawns/ExeRunCharacter.h"

UExeRunInputHandler_Jump::UExeRunInputHandler_Jump()
{
	TriggerEvents.Add(ETriggerEvent::Started);
	TriggerEvents.Add(ETriggerEvent::Completed);
}
 
void UExeRunInputHandler_Jump::HandleStartedEvent_Implementation(
	UNinjaInputManagerComponent* Manager,
	const FInputActionValue& Value, 
	const UInputAction* InputAction) const
{
	const AExeRunCharacter* Character = Cast<AExeRunCharacter>(Manager->GetPawn());
	if (!ensureAlways(IsValid(Character))) return;

	const UExeRunMoverComponent* MoverComponent = Character->GetMoverComponent();
	if (!ensureAlways(IsValid(MoverComponent))) return;
	
	UInputProducer_Character* InputProducer = MoverComponent->FindProducer<UInputProducer_Character>();
	if (!ensureAlways(IsValid(InputProducer))) return;
	
	InputProducer->SetJumpJustPressed(!InputProducer->GetJumpJustPressed());
	InputProducer->SetJumpJustPressed(true);
}

void UExeRunInputHandler_Jump::HandleCompletedEvent_Implementation(
	UNinjaInputManagerComponent* Manager,
	const FInputActionValue& Value, 
	const UInputAction* InputAction, 
	float ElapsedTime) const
{
	const AExeRunCharacter* Character = Cast<AExeRunCharacter>(Manager->GetPawn());
	if (!ensureAlways(IsValid(Character))) return;

	const UExeRunMoverComponent* MoverComponent = Character->GetMoverComponent();
	if (!ensureAlways(IsValid(MoverComponent))) return;
	
	UInputProducer_Character* InputProducer = MoverComponent->FindProducer<UInputProducer_Character>();
	if (!ensureAlways(IsValid(InputProducer))) return;
	
	InputProducer->SetJumpJustPressed(false);
	InputProducer->SetJumpJustPressed(false);
}
