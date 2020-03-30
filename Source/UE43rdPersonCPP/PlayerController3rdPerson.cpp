// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController3rdPerson.h"
#include "UE43rdPersonCPPCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"
#include "Components/InputComponent.h"
#include "UE43rdPersonCPPGameMode.h"


DECLARE_LOG_CATEGORY_EXTERN(CaptainsLog, Log, All);


APlayerController3rdPerson::APlayerController3rdPerson(const FObjectInitializer& ObjectInitializer)
{
	UE_LOG(CaptainsLog, Log, TEXT("APlayerController3rdPerson::APlayerController3rdPerson()")); //Log Entry
	CurrentActor = 0;	//Set to first Actor
}

//Allow us to get input
void APlayerController3rdPerson::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (IsValid(InputComponent))
	{
		UE_LOG(CaptainsLog, Log, TEXT("APlayerController3rdPerson::SetupInputComponent()")); //Log Entry
		InputComponent->BindAction("Jump", IE_Pressed, this, &APlayerController3rdPerson::Jump);
		InputComponent->BindAction("Jump", IE_Released, this, &APlayerController3rdPerson::StopJumping);

		InputComponent->BindAction("NextCharacter", IE_Pressed, this, &APlayerController3rdPerson::NextCharacter);
		InputComponent->BindAction("PreviousCharacter", IE_Pressed, this, &APlayerController3rdPerson::PrevCharacter);

		InputComponent->BindAxis("MoveForward", this, &APlayerController3rdPerson::MoveForward);
		InputComponent->BindAxis("MoveRight", this, &APlayerController3rdPerson::MoveRight);

		// We have 2 versions of the rotation bindings to handle different kinds of devices differently
		// "turn" handles devices that provide an absolute delta, such as a mouse.
		// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
		InputComponent->BindAxis("Turn", this, &APlayerController3rdPerson::YawInput);
		InputComponent->BindAxis("TurnRate", this, &APlayerController3rdPerson::TurnAtRate);
		InputComponent->BindAxis("LookUp", this, &APlayerController3rdPerson::PitchInput);
		InputComponent->BindAxis("LookUpRate", this, &APlayerController3rdPerson::LookUpAtRate);

	}
	else
	{
		UE_LOG(CaptainsLog, Error, TEXT("Invalid InputComponent")); //Log Error
	}
}

void APlayerController3rdPerson::BeginPlay()
{
	Super::BeginPlay();
	AUE43rdPersonCPPGameMode* tMyGameMode = AUE43rdPersonCPPGameMode::GetMyGameMode(this); //Use helper
	if (IsValid(tMyGameMode))
	{
		tMyGameMode->AddController(this);
	}
}

void APlayerController3rdPerson::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	AUE43rdPersonCPPGameMode* tMyGameMode = AUE43rdPersonCPPGameMode::GetMyGameMode(this); //Use helper
	if (IsValid(tMyGameMode))
	{
		tMyGameMode->RemoveController(this);
	}
}

//Pass to Character
void APlayerController3rdPerson::Jump()
{
	AUE43rdPersonCPPCharacter* tCharacter = Cast<AUE43rdPersonCPPCharacter>(GetPawn());
	if (IsValid(tCharacter)) 
	{
		tCharacter->Jump();
	}
}

void APlayerController3rdPerson::StopJumping()
{
	AUE43rdPersonCPPCharacter* tCharacter = Cast<AUE43rdPersonCPPCharacter>(GetPawn());
	if (IsValid(tCharacter))
	{
		tCharacter->StopJumping();
	}
}


void APlayerController3rdPerson::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AUE43rdPersonCPPCharacter* tCharacter = Cast<AUE43rdPersonCPPCharacter>(GetPawn());
	if (IsValid(tCharacter))
	{
		tCharacter->AddControllerYawInput(Rate * tCharacter->BaseTurnRate * GetWorld()->GetDeltaSeconds());
	}
}

void APlayerController3rdPerson::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AUE43rdPersonCPPCharacter* tCharacter = Cast<AUE43rdPersonCPPCharacter>(GetPawn());
	if (IsValid(tCharacter))
	{
		tCharacter->AddControllerPitchInput(Rate * tCharacter->BaseLookUpRate * GetWorld()->GetDeltaSeconds());
	}
}

void APlayerController3rdPerson::MoveForward(float Value)
{
	AUE43rdPersonCPPCharacter* tCharacter = Cast<AUE43rdPersonCPPCharacter>(GetPawn());
	if (IsValid(tCharacter) && ((tCharacter->Controller != NULL) && (Value != 0.0f)))
	{
		// find out which way is forward
		const FRotator Rotation = tCharacter->Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		tCharacter->AddMovementInput(Direction, Value);
	}
}

void APlayerController3rdPerson::MoveRight(float Value)
{
	AUE43rdPersonCPPCharacter* tCharacter = Cast<AUE43rdPersonCPPCharacter>(GetPawn());
	if (IsValid(tCharacter) && ((tCharacter->Controller != NULL) && (Value != 0.0f)))
	{
		// find out which way is right
		const FRotator Rotation = tCharacter->Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		tCharacter->AddMovementInput(Direction, Value);
	}
}

void APlayerController3rdPerson::YawInput(float Value)
{
	AUE43rdPersonCPPCharacter* tCharacter = Cast<AUE43rdPersonCPPCharacter>(GetPawn());
	if (IsValid(tCharacter))
	{
		tCharacter->AddControllerYawInput(Value);
	}
}

void APlayerController3rdPerson::PitchInput(float Value)
{
	AUE43rdPersonCPPCharacter* tCharacter = Cast<AUE43rdPersonCPPCharacter>(GetPawn());
	if (IsValid(tCharacter))
	{
		tCharacter->AddControllerPitchInput(Value);
	}
}

void APlayerController3rdPerson::NextCharacter()
{
	AUE43rdPersonCPPGameMode* myGameMode= AUE43rdPersonCPPGameMode::GetMyGameMode(this);
	if (IsValid(myGameMode))
	{
		int tCount = myGameMode->GetActorCount();
		if (tCount > 0)
		{
			CurrentActor = CurrentActor + 1;
			if (CurrentActor >= tCount)	CurrentActor = 0;	//Loop
			AUE43rdPersonCPPCharacter* PossessActor = myGameMode->GetActorAtIndex(CurrentActor);
			if (IsValid(PossessActor))
			{
				Possess(PossessActor);
				UE_LOG(CaptainsLog, Log, TEXT("Possessing %s"),*PossessActor->GetName()); //Log Entry
				return;
			}
		}
	}
	UE_LOG(CaptainsLog, Error, TEXT("NextCharacter() Error")); //Log Entry
}

void APlayerController3rdPerson::PrevCharacter()
{
	AUE43rdPersonCPPGameMode* myGameMode = AUE43rdPersonCPPGameMode::GetMyGameMode(this);
	if (IsValid(myGameMode))
	{
		int tCount = myGameMode->GetActorCount();
		if (tCount > 0)
		{
			CurrentActor = CurrentActor - 1;
			if (CurrentActor <0 )	CurrentActor = tCount-1;	//Loop
			AUE43rdPersonCPPCharacter* PossessActor = myGameMode->GetActorAtIndex(CurrentActor);
			if (IsValid(PossessActor))
			{
				Possess(PossessActor);
				UE_LOG(CaptainsLog, Log, TEXT("Possessing %s"), *PossessActor->GetName()); //Log Entry
				return;
			}
		}
	}
	UE_LOG(CaptainsLog, Error, TEXT("NextCharacter() Error")); //Log Entry
}


