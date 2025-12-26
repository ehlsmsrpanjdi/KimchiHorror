// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity/C_EntityBase.h"
#include "C_DocPatient.generated.h"

/**
 *
 */
UCLASS()
class HORRORPROTOKIMCHI_API AC_DocPatient : public AC_EntityBase
{
	GENERATED_BODY()

public:

	AC_DocPatient();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAudioComponent* SoundComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAudioComponent* HeartBeatComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class USoundBase*> PatientSoundArray;

	UFUNCTION(BlueprintCallable)
	bool OnEvent(float _DeltaTime);

	UFUNCTION(BlueprintCallable)
	bool OnCurePatient(int32 _AmpleIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentEventIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentTime = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CoolTime = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool HaveToCure = false;

};
