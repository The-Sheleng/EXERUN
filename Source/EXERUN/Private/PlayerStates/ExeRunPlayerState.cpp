// © 2026 Andrii Shelenhivskyi. Licensed under Creative Commons Attribution-NonCommercial 4.0.

#include "PlayerStates/ExeRunPlayerState.h"

#include "AbilitySystem/Components/ExeRunAbilitySystemComponent.h"
#include "Pawns/ExeRunCharacter.h"

UAbilitySystemComponent* AExeRunPlayerState::GetAbilitySystemComponent() const
{
	const AExeRunCharacter* CastedCharacter = GetPawn<AExeRunCharacter>();
	if (!ensureAlways(IsValid(CastedCharacter))) return nullptr;
	
	return CastedCharacter->GetAbilitySystemComponent();
}

const UExeRunAbilitySystemComponent* AExeRunPlayerState::GetExeRunAbilitySystemComponent() const
{
	const AExeRunCharacter* CastedCharacter = GetPawn<AExeRunCharacter>();
	if (!ensureAlways(IsValid(CastedCharacter))) return nullptr;
	
	return CastedCharacter->GetExeRunAbilitySystemComponent();
}
