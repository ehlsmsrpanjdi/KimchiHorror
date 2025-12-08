// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity/C_ActorBase.h"
#include "Components/AudioComponent.h"   // AudioComponent 헤더
#include "Sound/SoundBase.h"             // Sound asset 헤더
#include "C_ChildSpawner.generated.h"

/**
 * 
 */
UCLASS()
class HORRORPROTOKIMCHI_API AC_ChildSpawner : public AC_ActorBase
{
	GENERATED_BODY()

public:
	AC_ChildSpawner();


public:

	virtual void SetActiveFalse() override;

	virtual void SetActiveTrue() override;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sound")
	UAudioComponent* AudioComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound")
	USoundBase* SoundCue;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsActive = false;
};
