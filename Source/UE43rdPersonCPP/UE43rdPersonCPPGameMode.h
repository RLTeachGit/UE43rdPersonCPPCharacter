// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UE43rdPersonCPPGameMode.generated.h"

UCLASS(minimalapi)
class AUE43rdPersonCPPGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AUE43rdPersonCPPGameMode();

//New Code
private:
	//Will be an array of Actors
	UPROPERTY()
	TArray<class AUE43rdPersonCPPCharacter*> Characters;

	//Will be an array of Controllers
	UPROPERTY()
	TArray<class APlayerController3rdPerson*> Controllers;

public:
	void	AddCharacter(AUE43rdPersonCPPCharacter* Character);
	void	RemoveCharacter(AUE43rdPersonCPPCharacter* Character);
	int	GetActorCount();
	AUE43rdPersonCPPCharacter* GetActorAtIndex(int Index);

	void	AddController(APlayerController3rdPerson* Controller);
	void	RemoveController(APlayerController3rdPerson* Controller);
	int	GetControllerCount();
	APlayerController3rdPerson* GetControllerAtIndex(int Index);

	//Helper to get Correct GameMode, IE. this one, super safe
	static	AUE43rdPersonCPPGameMode* GetMyGameMode(AActor* myActor);


protected:
	virtual void	Tick(float DeltaTime) override;

private:
	float Timeout;
	const float Swaptime = 10.0f;


	int CurrentActor = 0;
};



