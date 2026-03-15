// © 2026 Andrii Shelenhivskyi. Licensed under Creative Commons Attribution-NonCommercial 4.0.

#include "Pawns/ExeRunCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "DefaultMovementSet/NavMoverComponent.h"
#include "NinjaInputHandler.h"
#include "Data/NinjaInputSetupDataAsset.h"
#include "NinjaInput/Components/ExeRunInputManagerComponent.h"
#include "NinjaInput/InputHandlers/MoverInputHandlers/MoverInputHandler.h"
#include "Controllers/PlayerControllers/ExeRunPlayerController.h"
#include "Mover/Components/ExeRunMoverComponent.h"

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
	
	SetNetUpdateFrequency(60.0f);
	
	PrimaryActorTick.bCanEverTick = false;

	/** Movement replication handled by mover */
	SetReplicatingMovement(false);
}

void AExeRunCharacter::ProduceInput_Implementation(int32 SimTimeMs, FMoverInputCmdContext& InputCmdResult)
{
	FCharacterDefaultInputs& CharacterInputs =
		InputCmdResult.InputCollection.FindOrAddMutableDataByType<FCharacterDefaultInputs>();

	/** Pawn is not possessed */
	if (!IsValid(Controller))
	{
		if (GetLocalRole() == ROLE_Authority && GetRemoteRole() == ROLE_SimulatedProxy)
		{
			static const FCharacterDefaultInputs DoNothingInput;
			CharacterInputs = DoNothingInput;
		}

		return;
	}

	CharacterInputs.ControlRotation = Controller->GetControlRotation();

	/** Collects input from NinjaInput handlers and feeds mover simulation */

	const AExeRunPlayerController* PlayerController = Cast<AExeRunPlayerController>(Controller);

	if (!IsValid(PlayerController)) return;

	UExeRunInputManagerComponent* InputManager = PlayerController->GetInputManagerComponent();

	if (!IsValid(InputManager)) return;

	for (const UNinjaInputSetupDataAsset* Setup : InputManager->GetInputHandlerSetups())
	{
		for (UNinjaInputHandler* InputHandler : Setup->InputHandlers)
		{
			if (UMoverInputHandler* CastedInputHandler = Cast<UMoverInputHandler>(InputHandler))
			{
				CastedInputHandler->ProduceInput(InputManager, SimTimeMs, InputCmdResult);
			}
		}
	}
}
