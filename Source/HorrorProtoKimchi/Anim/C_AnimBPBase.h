// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "C_FacePoseEnum.h"
#include "C_AnimBPBase.generated.h"

/**
 * 
 */
UCLASS()
class HORRORPROTOKIMCHI_API UC_AnimBPBase : public UAnimInstance
{
	GENERATED_BODY()
	
public : 
	
	

	UFUNCTION(BlueprintCallable)
	void SetFacePose(C_FacePoseEnum pose,float interval);
	
	UFUNCTION()
	int32 RandomIndex(int32 first,int32 last );


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float ElapsedTime = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Index = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 FirstIndex = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 LastIndex = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Interval = 0.1;
	

protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

};
