// © 2026 Andrii Shelenhivskyi. Licensed under Creative Commons Attribution-NonCommercial 4.0.

#pragma once

#include "AbilitySystemInterface.h"
#include "AbilitySystem/Components/ExeRunAbilitySystemComponent.h"
#include "ExeRunCharacter.generated.h"

class UCapsuleComponent;
class USpringArmComponent;
class UCameraComponent;
class UExeRunMoverComponent;
class UNavMoverComponent;

/**
 * Main playable pawn used in ExeRun project.
 *
 * Character is based on APawn instead of ACharacter and relies on
 * CharacterMoverComponent for movement simulation and replication.
 */
UCLASS()
class EXERUN_API AExeRunCharacter : public APawn, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	/** Returns collision capsule component */
	UCapsuleComponent* GetCapsuleComponent() const { return CapsuleComponent; }

	/** Returns skeletal mesh component */
	USkeletalMeshComponent* GetMesh() const { return MeshComponent; }

	/** Returns camera spring arm */
	USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns follow camera */
	UCameraComponent* GetCamera() const { return FollowCamera; }

	/** Returns main mover component */
	UExeRunMoverComponent* GetMoverComponent() const { return MoverComponent; }

	/** Returns navigation mover component */
	UNavMoverComponent* GetNavMoverComponent() const { return NavMoverComponent; }

	/** Returns ability system component component */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }

	/** Returns ability system component component */
	const UExeRunAbilitySystemComponent* GetExeRunAbilitySystemComponent() const { return AbilitySystemComponent; }

	AExeRunCharacter();


private:

	/** Character collision capsule */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

	/** Character visual mesh */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	TObjectPtr<USkeletalMeshComponent> MeshComponent;

	/** Camera spring arm controlling distance and rotation */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components|Camera", meta=(AllowPrivateAccess="true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	/** Player follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components|Camera", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UCameraComponent> FollowCamera;

	/** Networked movement simulation component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components|Mover", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UExeRunMoverComponent> MoverComponent;

	/** Navigation movement bridge */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components|Mover", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UNavMoverComponent> NavMoverComponent;

	/** Ability System Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components|GAS", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UExeRunAbilitySystemComponent> AbilitySystemComponent;
};
