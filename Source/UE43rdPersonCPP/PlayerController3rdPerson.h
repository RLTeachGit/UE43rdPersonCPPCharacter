// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerController3rdPerson.generated.h"


/**
 * 
 */
UCLASS()
class UE43RDPERSONCPP_API APlayerController3rdPerson : public APlayerController
{
	GENERATED_BODY()


	//New Code

	APlayerController3rdPerson(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void SetupInputComponent() override; //Override default

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	//Action/Axis mapping

	void Jump();

	void StopJumping();

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

	void MoveForward(float Value);

	void MoveRight(float Value);

	void YawInput(float Value);

	void PitchInput(float Value);

	void NextCharacter();
	void PrevCharacter();

private:
	int CurrentActor;

};
