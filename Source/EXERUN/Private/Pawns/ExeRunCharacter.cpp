// © 2026 Andrii Shelenhivskyi. Licensed under Creative Commons Attribution-NonCommercial 4.0.

#include "Pawns/ExeRunCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Mover/Components/ExeRunMoverComponent.h"
#include "DefaultMovementSet/NavMoverComponent.h"

AExeRunCharacter::AExeRunCharacter()
{
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->InitCapsuleSize(42.f, 96.f);
	CapsuleComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	CapsuleComponent->CanCharacterStepUpOn = ECB_No;
	CapsuleComponent->SetShouldUpdatePhysicsVolume(true);
	CapsuleComponent->SetCanEverAffectNavigation(false);
	CapsuleComponent->bDynamicObstacle = true;

	RootComponent = CapsuleComponent;

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(CapsuleComponent);
	MeshComponent->AlwaysLoadOnClient = true;
	MeshComponent->AlwaysLoadOnServer = true;
	MeshComponent->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPose;
	MeshComponent->bCastDynamicShadow = true;
	MeshComponent->bAffectDynamicIndirectLighting = true;
	MeshComponent->PrimaryComponentTick.TickGroup = TG_PrePhysics;
	MeshComponent->SetCollisionProfileName(TEXT("CharacterMesh"));
	MeshComponent->SetGenerateOverlapEvents(true);
	MeshComponent->SetCanEverAffectNavigation(false);
	MeshComponent->SetUsingAbsoluteRotation(true);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(MeshComponent);
	CameraBoom->TargetArmLength = 400.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	MoverComponent = CreateDefaultSubobject<UExeRunMoverComponent>(TEXT("MoverComponent"));
	NavMoverComponent = CreateDefaultSubobject<UNavMoverComponent>(TEXT("NavMoverComponent"));

	AbilitySystemComponent = CreateDefaultSubobject<UExeRunAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	PrimaryActorTick.bCanEverTick = false;

	/** Movement replication handled by mover */
	SetReplicatingMovement(false);
}
