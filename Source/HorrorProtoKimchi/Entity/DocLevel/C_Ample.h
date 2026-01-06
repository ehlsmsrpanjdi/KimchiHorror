// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_Ample.generated.h"

UCLASS()
class HORRORPROTOKIMCHI_API AC_Ample : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AC_Ample();

	UFUNCTION(BlueprintCallable)
	bool InteractionDrug();

	//주사기에 약 주입
	UFUNCTION(BlueprintCallable)
	void AddDrug();

	//약 손에 들기
	UFUNCTION(BlueprintCallable)
	void GainDrug();

	UFUNCTION(BlueprintCallable)
	void EndInteraction();


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DrugIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AC_Crate* CurrentCrate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentCrateIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsInteracting = false;
};
