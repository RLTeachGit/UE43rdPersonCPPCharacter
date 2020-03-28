// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "UE43rdPersonCPPGameMode.h"
#include "UE43rdPersonCPPCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUE43rdPersonCPPGameMode::AUE43rdPersonCPPGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
