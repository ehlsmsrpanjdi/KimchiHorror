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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAudioComponent* SoundComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class USoundBase*> PatientSoundArray;

	UFUNCTION(BlueprintCallable)
	void OnEvent();
};
