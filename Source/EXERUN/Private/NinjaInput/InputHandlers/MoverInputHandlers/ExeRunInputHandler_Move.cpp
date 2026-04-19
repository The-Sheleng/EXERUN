// © 2026 Andrii Shelenhivskyi. Licensed under Creative Commons Attribution-NonCommercial 4.0.

#include "NinjaInput/InputHandlers/MoverInputHandlers/ExeRunInputHandler_Move.h"

#include "Components/NinjaInputManagerComponent.h"
#include "Mover/InputProducers/InputProducer_Character.h"
#include "Pawns/ExeRunCharacter.h"

UExeRunInputHandler_Move::UExeRunInputHandler_Move()
{
	TriggerEvents.Add(ETriggerEvent::Triggered);
	TriggerEvents.Add(ETriggerEvent::Completed);
}

void UExeRunInputHandler_Move::HandleTriggeredEvent_Implementation(
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
	
	const FVector MovementVector = Value.Get<FVector>();
	
	FVector Input;
	Input.X = FMath::Clamp(MovementVector.X, -1.0f, 1.0f);
	Input.Y = FMath::Clamp(MovementVector.Y, -1.0f, 1.0f);
	Input.Z = FMath::Clamp(MovementVector.Z, -1.0f, 1.0f);
	
	InputProducer->SetMoveIntent(Input);
}

void UExeRunInputHandler_Move::HandleCompletedEvent_Implementation(
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
	if (ensureAlways(IsValid(InputProducer)))
	{
		InputProducer->SetMoveIntent(FVector::ZeroVector);
	}
}
