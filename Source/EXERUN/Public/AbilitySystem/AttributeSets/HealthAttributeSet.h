// © 2026 Andrii Shelenhivskyi. Licensed under Creative Commons Attribution-NonCommercial 4.0.

#pragma once

#include "CoreMinimal.h"
#include "ExeRunAttributeSet.h"
#include "HealthAttributeSet.generated.h"

/** Contains Health and MaxHealth attributes */
UCLASS()
class EXERUN_API UHealthAttributeSet : public UExeRunAttributeSet
{
	GENERATED_BODY()

public:
	/** Current health of the character */
	ATTRIBUTE_GETTERS(ThisClass, Health);
	
	/** Maximum possible health of the character */
	ATTRIBUTE_GETTERS(ThisClass, MaxHealth);
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;


protected:

	virtual void ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const override;

	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;


private:
	
	UPROPERTY(Transient, ReplicatedUsing="OnRep_Health")
	FGameplayAttributeData Health = 100;
	
	UPROPERTY(Transient, ReplicatedUsing="OnRep_Health")
	FGameplayAttributeData MaxHealth = 100;
	
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue) const;
};
