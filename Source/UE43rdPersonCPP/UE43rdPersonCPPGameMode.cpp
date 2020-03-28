// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "UE43rdPersonCPPGameMode.h"
#include "UE43rdPersonCPPCharacter.h"
#include "UObject/ConstructorHelpers.h"

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
		UE_LOG(LogTemp, Error, TEXT("Cannot find DefaultPawnClass:%s"), tPlayerClassName); //Log Error
	}

	static ConstructorHelpers::FClassFinder<AController> PlayerControllerBPClass(tPlayerControllerName); //Use the controller we created instead
	if (PlayerControllerBPClass.Succeeded())
	{
		PlayerControllerClass = PlayerControllerBPClass.Class; //Set our controller as default
	}
	else
	{
		PlayerControllerClass = NULL; ///If we dont do this it will contain rubbish and crash
		UE_LOG(LogTemp, Error, TEXT("Cannot find PlayerControllerClass:%s"), tPlayerControllerName); //Log Error
	}
}
