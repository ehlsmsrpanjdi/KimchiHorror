// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Anim/C_EntityMoveEnum.h"
#include "C_EntityAnimBase.generated.h"

/**
 * 
 */
UCLASS()
class HORRORPROTOKIMCHI_API UC_EntityAnimBase : public UAnimInstance
{
	GENERATED_BODY()

public :
	


	UFUNCTION(BlueprintCallable)
	void SetBodyMove(C_EntityMoveEnum pose);
	UFUNCTION(BlueprintCallable)
	void LerfTiltHead( FVector des, float speed = 1.f);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Index;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector TiltHead;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector TargetHeadTilt;
	
private : 
	float TiltSpeed;
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
