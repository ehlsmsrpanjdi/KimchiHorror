// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity/Stage_1/C_HospitalChild.h"
#include "C_HideChild.generated.h"

/**
 *
 */
UCLASS()
class HORRORPROTOKIMCHI_API AC_HideChild : public AC_HospitalChild
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	bool MoveFunction();

	void CheckFindPlayer();

	UFUNCTION(BlueprintCallable)
	bool CheckCoolTime(float _Deltatime);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* locationComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float activeTime = 2;
	float currentActiveTime = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool FindPlayer = false;
};
