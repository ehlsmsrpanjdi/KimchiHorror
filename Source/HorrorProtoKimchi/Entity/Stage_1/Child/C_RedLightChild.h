// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity/Stage_1/C_HospitalChild.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
#include "C_RedLightChild.generated.h"

/**
 *
 */
UCLASS()
class HORRORPROTOKIMCHI_API AC_RedLightChild : public AC_HospitalChild
{
	GENERATED_BODY()


public:

	AC_RedLightChild();



public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* RedLightSound;


	UAudioComponent* AudioComponent;
	FTimerHandle SoundFinishedTimer;

	UFUNCTION(BlueprintCallable)
	void OnSoundFinished();

	UFUNCTION(BlueprintCallable)
	void PlayRedLight();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsChecking = false;

	UFUNCTION(BlueprintCallable)
	void StopRedLightGame();




	UFUNCTION(BlueprintCallable)
	void SetDirectionToForward();

	UFUNCTION(BlueprintCallable)
	void SetDirectionToBack();

	UFUNCTION(BlueprintCallable)
	bool CheckPlayerMove();


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector LookDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* ForwardDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* BackDirection;
};
