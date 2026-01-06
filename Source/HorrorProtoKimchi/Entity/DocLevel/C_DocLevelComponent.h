// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_Syringe.h"
#include "C_Ample.h"
#include "C_DocLevelComponent.generated.h"


UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class HORRORPROTOKIMCHI_API UC_DocLevelComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UC_DocLevelComponent();

protected:

public:

	UFUNCTION(BlueprintCallable)
	void GainSyringe();

	UFUNCTION(BlueprintCallable)
	void AddDrug(AC_Ample* Ample);

	UFUNCTION(BlueprintCallable)
	void GainAmple(AC_Ample* Ample);

	UFUNCTION(BlueprintCallable)
	void NurseLeave();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void DocAngry();

	UFUNCTION(BlueprintCallable)
	void UseAmple();

	UFUNCTION(BlueprintCallable)
	void WasteSyringe();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AC_Ample* SelectedAmple;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AC_Syringe* SelectedSyringe;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SelectedDrugIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bOnAmple;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentNurseCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AC_Syringe> SyringeClass;
};
