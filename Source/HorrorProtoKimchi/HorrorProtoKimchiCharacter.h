// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Components/ArrowComponent.h"
#include "HorrorProtoKimchiCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
class AC_EntityBase;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 *  A simple player-controllable third person character
 *  Implements a controllable orbiting camera
 */
UCLASS(abstract)
class AHorrorProtoKimchiCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UArrowComponent* TargetComponent;

protected:

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookAction;

	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MouseLookAction;

	/** Interaction Input Action */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* InteractionAction;

	/** Interaction Input Action */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* CrouchAction;

public:

	/** Constructor */
	AHorrorProtoKimchiCharacter();

protected:
	virtual void BeginPlay() override;

	void CheckInteraction();
	UPROPERTY()
	TArray<AActor*> ActorsToIgnore;
public:
	virtual void Tick(float _DeltaTime) override;

protected:

	/** Initialize input action bindings */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);


public:

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoMove(float Right, float Forward);

	/** Handles look inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoLook(float Yaw, float Pitch);

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoJumpStart();

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoJumpEnd();

public:

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }


#pragma region "여기서부터 추가한 클래스들"

public:
	void Interaction(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoInteraction();

	void CrouchFunction(const FInputActionValue& _Value);

	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoCrouchFunction();

	UFUNCTION(BlueprintCallable)
	virtual FVector GetTargetPos();

protected:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	AActor* CurrentInteractActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	AActor* PreviousInteractActor = nullptr;
#pragma endregion

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxDoubtGauge = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentDoubtGauge = 0.f;

	UFUNCTION(BlueprintCallable)
	bool AddDoubt(float _Value);
	UFUNCTION(BlueprintCallable)
	bool IsDoubtMode();

	UPROPERTY()
	bool alreadyMax = false;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHp = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentHp = 100.f;

	UFUNCTION(BlueprintCallable)
	bool PlayerTakeDamage(float _Value);

	//의심도 연출용 재정의함수
	UFUNCTION(BlueprintImplementableEvent, Category = "Noise")
	void SetNoise(int32 Doubt);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsHide = false;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PlayerYaw;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PlayerPitch;
};

