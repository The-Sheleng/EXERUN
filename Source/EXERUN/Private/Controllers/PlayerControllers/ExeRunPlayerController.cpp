// © 2026 Andrii Shelenhivskyi. Licensed under Creative Commons Attribution-NonCommercial 4.0.

#include "Controllers/PlayerControllers/ExeRunPlayerController.h"

#include "Components/NinjaInputManagerComponent.h"
#include "Pawns/ExeRunCharacter.h"

UAbilitySystemComponent* AExeRunPlayerController::GetAbilitySystemComponent() const
{
	const AExeRunCharacter* CastedCharacter = GetPawn<AExeRunCharacter>();
	if (!ensureAlways(IsValid(CastedCharacter))) return nullptr;
	
	return CastedCharacter->GetAbilitySystemComponent();
}

const UExeRunAbilitySystemComponent* AExeRunPlayerController::GetExeRunAbilitySystemComponent() const
{
	const AExeRunCharacter* CastedCharacter = GetPawn<AExeRunCharacter>();
	if (!ensureAlways(IsValid(CastedCharacter))) return nullptr;
	
	return CastedCharacter->GetExeRunAbilitySystemComponent();
}

AExeRunPlayerController::AExeRunPlayerController()
{
	InputManagerComponent = CreateDefaultSubobject<UNinjaInputManagerComponent>(TEXT("InputManagerComponent"));
}
