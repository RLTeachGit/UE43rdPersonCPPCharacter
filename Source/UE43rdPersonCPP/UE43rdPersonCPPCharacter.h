// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UE43rdPersonCPPCharacter.generated.h"

//Forward ref
class AUE43rdPersonCPPGameMode;

UCLASS(config=Game)
class AUE43rdPersonCPPCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AUE43rdPersonCPPCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;


public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }



//NEW CODE

	//Deal with Possession
protected:
	virtual void PossessedBy(AController* Controller) override;
	virtual void UnPossessed(void) override;

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

//New Variables
public:

	/** Materials in use */
	UPROPERTY(EditDefaultsOnly, Category = PlayerColour)
	class UMaterialInstance* NormalMaterialBody;

	UPROPERTY(EditDefaultsOnly, Category = PlayerColour)
	class UMaterialInstance* NormalMaterialChest;

	UPROPERTY(EditDefaultsOnly, Category = PlayerColour)
	class UMaterialInstance* PossessedMaterialBody;

	UPROPERTY(EditDefaultsOnly, Category = PlayerColour)
	class UMaterialInstance* PossessedMaterialChest;

};

