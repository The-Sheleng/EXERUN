// © 2026 Andrii Shelenhivskyi. Licensed under Creative Commons Attribution-NonCommercial 4.0.

#pragma once

#include "CoreMinimal.h"
#include "Components/NinjaInputManagerComponent.h"
#include "NinjaInput/Common/Structs/InputHandleCacheBase.h"
#include "ExeRunInputManagerComponent.generated.h"

/**
 * ExeRun input manager responsible for:
 *
 * - storing active input mapping contexts
 * - managing NinjaInput handler setups
 * - caching input handles used during mover simulation
 *
 * Acts as a central runtime input subsystem owned by PlayerController.
 */
UCLASS(ClassGroup=(Input), meta=(BlueprintSpawnableComponent))
class EXERUN_API UExeRunInputManagerComponent : public UNinjaInputManagerComponent
{
	GENERATED_BODY()

public:

	/** Returns standalone mapping contexts applied independently of setups */
	const TArray<TObjectPtr<UInputMappingContext>>& GetStandaloneContexts() const { return StandaloneContexts; }

	/** Returns configured Ninja input handler setups */
	const TArray<TObjectPtr<UNinjaInputSetupDataAsset>>& GetInputHandlerSetups() const { return InputHandlerSetup; }

	/**
	 * Finds or creates cached input handle storage for a given type.
	 *
	 * Cache lifetime equals component lifetime.
	 * Used to avoid per-frame allocations during input production.
	 */
	template<typename T>
	T& FindOrAddInputHandleCacheByType()
	{
		static_assert(TIsDerivedFrom<T, FInputHandleCacheBase>::IsDerived, "T must derive from FInputHandleCacheBase");

		const UScriptStruct* Type = T::StaticStruct();

		if (const TSharedPtr<FInputHandleCacheBase>* Found = InputHandleCaches.Find(Type))
		{
			return *static_cast<T*>(Found->Get());
		}

		TSharedPtr<T> NewCache = MakeShared<T>();
		InputHandleCaches.Add(Type, NewCache);

		return *NewCache;
	}

private:

	/** Runtime cache of input handles indexed by struct type. */
	TMap<const UScriptStruct*, TSharedPtr<FInputHandleCacheBase>> InputHandleCaches;
};