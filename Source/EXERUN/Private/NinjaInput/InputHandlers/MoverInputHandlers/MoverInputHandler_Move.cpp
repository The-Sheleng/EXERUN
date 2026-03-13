// © 2026 Andrii Shelenhivskyi. Licensed under Creative Commons Attribution-NonCommercial 4.0.

#include "NinjaInput/InputHandlers/MoverInputHandlers/MoverInputHandler_Move.h"

#include "NinjaInput/Components/ExeRunInputManagerComponent.h"
#include "DefaultMovementSet/NavMoverComponent.h"
#include "Pawns/ExeRunCharacter.h"

UMoverInputHandler_Move::UMoverInputHandler_Move()
{
	TriggerEvents.Add(ETriggerEvent::Triggered);
	TriggerEvents.Add(ETriggerEvent::Completed);
}

void UMoverInputHandler_Move::HandleTriggeredEvent_Implementation(
	UNinjaInputManagerComponent* Manager,
	const FInputActionValue& Value, 
	const UInputAction* InputAction, 
	float ElapsedTime) const
{
	UExeRunInputManagerComponent* CastedManager = Cast<UExeRunInputManagerComponent>(Manager);
	if (!ensureAlways(IsValid(CastedManager))) return;
		
	FMoveInputHandleCache& MoveCache = CastedManager->FindOrAddInputHandleCacheByType<FMoveInputHandleCache>();
	const FVector MovementVector = Value.Get<FVector>();

	MoveCache.Intent.X = FMath::Clamp(MovementVector.X, -1.0f, 1.0f);
	MoveCache.Intent.Y = FMath::Clamp(MovementVector.Y, -1.0f, 1.0f);
	MoveCache.Intent.Z = FMath::Clamp(MovementVector.Z, -1.0f, 1.0f);
}

void UMoverInputHandler_Move::HandleCompletedEvent_Implementation(
	UNinjaInputManagerComponent* Manager,
	const FInputActionValue& Value, 
	const UInputAction* InputAction, 
	float ElapsedTime) const
{
	UExeRunInputManagerComponent* CastedManager = Cast<UExeRunInputManagerComponent>(Manager);
	if (!ensureAlways(IsValid(CastedManager))) return;

	FMoveInputHandleCache& MoveCache = CastedManager->FindOrAddInputHandleCacheByType<FMoveInputHandleCache>();

	MoveCache.Intent = FVector::ZeroVector;
}

void UMoverInputHandler_Move::ProduceInput(
	UExeRunInputManagerComponent* Manager,
	int32 SimTimeMs,
	FMoverInputCmdContext& InputCmdResult)
{
	if (!ensureAlways(IsValid(Manager))) return;
		
	const APawn* Pawn = Manager->GetPawn();
	if (!ensureAlways(IsValid(Pawn))) return;
		
	FCharacterDefaultInputs& CharacterInputs =
		InputCmdResult.InputCollection.FindOrAddMutableDataByType<FCharacterDefaultInputs>();

	FMoveInputHandleCache& MoveInputCache =
		Manager->FindOrAddInputHandleCacheByType<FMoveInputHandleCache>();
		
	/** Control rotation represents player intent space */
	CharacterInputs.ControlRotation = Pawn->GetControlRotation();
		
	/** Navigation movement MAY inject movement requests */
	bool bRequestedNavMovement = false;
	UNavMoverComponent* NavMoverComponent = Pawn->FindComponentByClass<UNavMoverComponent>();
	if (IsValid(NavMoverComponent))
	{
		bRequestedNavMovement = NavMoverComponent->ConsumeNavMovementData(
		MoveInputCache.Intent,
		MoveInputCache.Velocity
		);
	}
	
	/**
	 * Movement Representation Selection:
	 * 1) DirectionalIntent (Player provides desired direction)
	 * 2) Velocity (External system already computed velocity)
	 *
	 * Velocity always has priority because it represents
	 * an already-resolved movement result.
	 */
	if (MoveInputCache.Velocity.IsZero())
	{
		const FVector FinalIntent = CharacterInputs.ControlRotation.RotateVector(MoveInputCache.Intent);
		CharacterInputs.SetMoveInput(EMoveInputType::DirectionalIntent, FinalIntent);
	}
	else
	{
		CharacterInputs.SetMoveInput(EMoveInputType::Velocity, MoveInputCache.Velocity);
	}

	/** Clear cached input if movement came from navigation */
	if (bRequestedNavMovement)
	{
		MoveInputCache.Intent = MoveInputCache.Velocity = FVector::ZeroVector;
	}

	/**
	 * Orientation Intent Resolution:
	 * OrientationIntent does NOT always equal movement direction.
	 * 
	 * Depending on configuration:
	 * - Character may face movement direction (action games)
	 * - Character may face camera direction (shooter controls)
	 */
	
	CharacterInputs.OrientationIntent = FVector::ZeroVector;
	
	/** Face control rotation */
	if (!bOrientRotationToMovement)
	{
		CharacterInputs.OrientationIntent = CharacterInputs.ControlRotation.Vector().GetSafeNormal();
	}
	/** Face direction of actual movement */
	else if (CharacterInputs.GetMoveInput().Size() >= RotationMagMin)
	{
		CharacterInputs.OrientationIntent = CharacterInputs.GetMoveInput().GetSafeNormal();

		/**
		 * Store last meaningful movement direction.
		 * Used when movement stops but orientation should persist.
		 */
		MoveInputCache.LastMoveInput = CharacterInputs.GetMoveInput();
	}
	else if (bMaintainLastInputOrientation)
	{
		/**
		 * Preserve previous facing direction when player stops moving.
		 * Prevents snapping orientation to zero when input magnitude drops.
		 */
		CharacterInputs.OrientationIntent = MoveInputCache.LastMoveInput.GetSafeNormal();;
	}
}
