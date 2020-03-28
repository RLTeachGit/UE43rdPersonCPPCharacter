// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "UE43rdPersonCPPGameMode.h"
#include "UE43rdPersonCPPCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "UE43rdPersonCPPCharacter.h"
#include "Engine/World.h"


DECLARE_LOG_CATEGORY_EXTERN(CaptainsLog, Log, All);


AUE43rdPersonCPPGameMode::AUE43rdPersonCPPGameMode()
{
	// set default pawn class to our Blueprinted character
//	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter")); //Default one
	//You can right click the asset to get the path in IDE
	auto tPlayerClassName = TEXT("/Game/NewBluePrints/UE43rdPersonCPPCharacterBP");  //BE CAREFUL UE4 will crash if these are not found

	auto tPlayerControllerName = TEXT("/Game/NewBluePrints/PlayerController3rdPersonBP");
	
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(tPlayerClassName); //Use the one we created instead
	if (PlayerPawnBPClass.Succeeded())
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	else 
	{
		DefaultPawnClass = NULL; //If we dont do this it will contain rubbish and crash
		UE_LOG(CaptainsLog, Error, TEXT("Cannot find DefaultPawnClass:%s"), tPlayerClassName); //Log Error
	}

	static ConstructorHelpers::FClassFinder<AController> PlayerControllerBPClass(tPlayerControllerName); //Use the controller we created instead
	if (PlayerControllerBPClass.Succeeded())
	{
		PlayerControllerClass = PlayerControllerBPClass.Class; //Set our controller as default
	}
	else
	{
		PlayerControllerClass = NULL; ///If we dont do this it will contain rubbish and crash
		UE_LOG(CaptainsLog, Error, TEXT("Cannot find PlayerControllerClass:%s"), tPlayerControllerName); //Log Error
	}

	//UE_LOG(CaptainsLog, Error, TEXT("I am an error")); //Log Error
	//UE_LOG(CaptainsLog, Warning, TEXT("I am an Warning")); //Log Warning
	//UE_LOG(CaptainsLog, Log, TEXT("I am a Log entry")); //Log Entry

}


//Called by actor when they add themselves to the scene on BeginPlay()
void AUE43rdPersonCPPGameMode::AddCharacter(AUE43rdPersonCPPCharacter* Character)
{
	Characters.Add(Character); //Add to Array of player characters
	UE_LOG(CaptainsLog, Log, TEXT("AddCharacter:%s Count %d"),*Character->GetName(), Characters.Num()); //Log Entry
}

//Called by actor when they removed themselves from the scene on EndPlay()
void AUE43rdPersonCPPGameMode::RemoveCharacter(AUE43rdPersonCPPCharacter* Character)
{
	Characters.Remove(Character);//Remove from Array of player characters
	UE_LOG(CaptainsLog, Log, TEXT("RemoveCharacter:%s Count %d"), *Character->GetName(),Characters.Num()); //Log Entry
}

//Static helper which tries to get the right GameMode From any context (with an Actor)
AUE43rdPersonCPPGameMode* AUE43rdPersonCPPGameMode::GetMyGameMode(AActor* myActor)
{
	//Get MyGameMode with all the casting and checks
	if (IsValid(myActor))
	{
		UWorld* tWorld = myActor->GetWorld();
		if (IsValid(tWorld))
		{
			AUE43rdPersonCPPGameMode* tGameMode = Cast<AUE43rdPersonCPPGameMode>(tWorld->GetAuthGameMode());
			if (IsValid(tGameMode))
			{
				return	tGameMode;
			}
			else
			{
				UE_LOG(CaptainsLog, Error, TEXT("No AUE43rdPersonCPPGameMode")); //Log Error
			}
		}
		else
		{
			UE_LOG(CaptainsLog, Error, TEXT("No World")); //Log Error
		}
	}
	else
	{
		UE_LOG(CaptainsLog, Error, TEXT("No Actor")); //Log Error
	}
	return nullptr;
}

//Helper function to get count of actors
int AUE43rdPersonCPPGameMode::GetActorCount()
{
	return Characters.Num();	//Count of current Actors
}

//Get the actor at a specified index (safe)
AUE43rdPersonCPPCharacter* AUE43rdPersonCPPGameMode::GetActorAtIndex(int Index)
{
	if (Characters.Num() > Index) 
	{
		return	Characters[Index];
	}
	return nullptr;
}
