// © 2026 Andrii Shelenhivskyi. Licensed under Creative Commons Attribution-NonCommercial 4.0.

#pragma once

#include "InputHandleCacheBase.generated.h"

/**
 * Base runtime cache for input handles.
 *
 * Acts as a polymorphic parent for typed input caches used
 * in the ExeRunInputManagerComponent.
 *
 * Lifetime is tied to the owning InputManagerComponent.
 */
USTRUCT(BlueprintType)
struct FInputHandleCacheBase
{
	GENERATED_BODY()

	/**
	 * Base struct intentionally empty.
	 * Typed caches should extend this struct.
	 */
};