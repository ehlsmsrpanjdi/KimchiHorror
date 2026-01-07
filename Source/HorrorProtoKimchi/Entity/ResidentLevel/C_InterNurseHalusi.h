// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity/C_EntityBase.h"
#include "C_InterNurseHalusi.generated.h"

/**
 *
 */
UCLASS()
class HORRORPROTOKIMCHI_API AC_InterNurseHalusi : public AC_EntityBase
{
	GENERATED_BODY()

public:
	AC_InterNurseHalusi();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bisInteracted = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsTrueNS = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsEnd = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AC_SequenceHelper* SequenceHelper;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Medicine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentPhase = 0;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void CorrectNurse();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void WrongNurse();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Sneer();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Shake();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OpenUP();

	UFUNCTION(BlueprintCallable)
	void InteractionEvent();

	//shake

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CoolTime = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentTime = 0;

	UFUNCTION(BlueprintCallable)
	bool CalculateShaking(float _DeltaTime);

	UFUNCTION(BlueprintCallable)
	void CalculateFace(float _DeltaTime);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void FaceFunction();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanShake = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FaceCoolTime = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FaceCurrentTime = 2;


	//activeatemode

	UFUNCTION(BlueprintCallable)
	void ActiveMode();

	UFUNCTION(BlueprintCallable)
	void SleepMode();

	void OffAll(bool _bool);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dormant")
	TArray<USkeletalMeshComponent*> DormantIncludeMeshes;
};
