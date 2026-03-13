// © 2026 Andrii Shelenhivskyi. Licensed under Creative Commons Attribution-NonCommercial 4.0.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystem/Components/ExeRunAbilitySystemComponent.h"
#include "ExeRunAttributeSet.generated.h"

/** This macro defines a set of helper functions for accessing and initializing attributes. */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	ATTRIBUTE_GETTERS(ClassName, PropertyName) \
	ATTRIBUTE_SETTERS(ClassName, PropertyName)

/** This macro defines a set of helper functions for getting attributes. */
#define ATTRIBUTE_GETTERS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)

/** This macro defines a set of helper functions for setting attributes and initializing. */
#define ATTRIBUTE_SETTERS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

class UExeRunAbilitySystemComponent;

/** Base attribute set class used in ExeRun project */
UCLASS(Abstract)
class EXERUN_API UExeRunAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	UExeRunAbilitySystemComponent* GetOwningExeRunAbilitySystemComponent() const
	{
		return CastChecked<UExeRunAbilitySystemComponent>(
			GetOwningAbilitySystemComponent(), 
			ECastCheckedType::NullAllowed);
	}
	
	
protected:
	
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
	/**
	 * Always called on PreAttributeChange. Should be overriden by clients 
	 * to clamp attribute values between allowed ranges.
	 */
	virtual void ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const PURE_VIRTUAL();
};
