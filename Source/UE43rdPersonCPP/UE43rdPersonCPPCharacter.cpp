// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "UE43rdPersonCPPCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h" //So we can set Material
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/MaterialInstance.h"
#include "PlayerController3rdPerson.h"
#include "UE43rdPersonCPPGameMode.h"


DECLARE_LOG_CATEGORY_EXTERN(CaptainsLog, Log, All);


//////////////////////////////////////////////////////////////////////////
// AUE43rdPersonCPPCharacter

AUE43rdPersonCPPCharacter::AUE43rdPersonCPPCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)



}


//Deal with player taking control
void AUE43rdPersonCPPCharacter::PossessedBy(AController* Controller)
{
	Super::PossessedBy(Controller); //Call parent, in case
	USkeletalMeshComponent* tMesh = GetMesh();
	APlayerController3rdPerson* tPlayerController = Cast< APlayerController3rdPerson>(Controller); //Is it player?
	if (IsValid(tPlayerController))
	{
		if (IsValid(tMesh) && IsValid(PossessedMaterialBody) && IsValid(PossessedMaterialChest))
		{
			tMesh->SetMaterial(0, PossessedMaterialBody);
			tMesh->SetMaterial(1, PossessedMaterialChest);
			UE_LOG(CaptainsLog, Log, TEXT("PossessedBy %s"), *Controller->GetName()); //Log Entry
		}
		else
		{
			UE_LOG(CaptainsLog, Error, TEXT("PossessedBy error")); //Log Error
		}
	}
	else 
	{
		UE_LOG(CaptainsLog, Warning, TEXT("Ignoring possession by %s"),*Controller->GetName()); //Log Warning
	}
}


//Called when we get UnPossessed
void AUE43rdPersonCPPCharacter::UnPossessed(void)
{
	Super::UnPossessed();
	USkeletalMeshComponent* tMesh = GetMesh();
	if (IsValid(tMesh) && IsValid(NormalMaterialBody) && IsValid(NormalMaterialChest))
	{
		tMesh->SetMaterial(0, NormalMaterialBody); //Set up Materials
		tMesh->SetMaterial(1, NormalMaterialChest);
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None); //Stop character moving
		UE_LOG(CaptainsLog, Log, TEXT("UnPossessed")); //Log Entry
	}
	else
	{
		UE_LOG(CaptainsLog, Error, TEXT("UnPossessed error")); //Log Error
	}
}


//Do this in Begin Play as world does not exist before
void AUE43rdPersonCPPCharacter::BeginPlay()
{
	Super::BeginPlay();
	AUE43rdPersonCPPGameMode* tMyGameMode = AUE43rdPersonCPPGameMode::GetMyGameMode(this); //Use helper
	if (IsValid(tMyGameMode))
	{
		tMyGameMode->AddCharacter(this); //Add to array in GameMode
	}
}

void AUE43rdPersonCPPCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	AUE43rdPersonCPPGameMode* tMyGameMode = AUE43rdPersonCPPGameMode::GetMyGameMode(this);
	if (IsValid(tMyGameMode))
	{
		tMyGameMode->RemoveCharacter(this); //Remove from array in GameMode
	}
}




/*Input now handled in controller, so all that code has moved to controller*/