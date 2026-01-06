// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_DoctorDoorKnockObj.generated.h"

UCLASS()
class HORRORPROTOKIMCHI_API AC_DoctorDoorKnockObj : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AC_DoctorDoorKnockObj();


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isEnd = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isKnoking = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentCoolTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CoolTime;

	UFUNCTION(BlueprintCallable)
	bool CalculateCoolTime(float _DeltaTime);

	UFUNCTION(BlueprintImplementableEvent)
	void EndEvent();
};
