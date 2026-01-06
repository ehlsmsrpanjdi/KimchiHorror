// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_Crate.generated.h"

UCLASS()
class HORRORPROTOKIMCHI_API AC_Crate : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AC_Crate();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<bool> isPutArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class AC_Ample*> AmplesArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UArrowComponent*> ArrowsArray;

	UFUNCTION(BlueprintCallable)
	void InteractionEvent();

	UFUNCTION(BlueprintCallable)
	void PutAmple(class AC_Ample* Ample);

	UFUNCTION(BlueprintCallable)
	void PutOffAmple(class AC_Ample* Ample);

	UFUNCTION(BlueprintCallable)
	void EHIHIEvent();

	UFUNCTION(BlueprintCallable)
	void SwapEHIHI();

	UFUNCTION(BlueprintCallable)
	void ReturnEHIHI();


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AC_Crate* OtherCrate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsAlreadyPut = false;

	UFUNCTION(BlueprintCallable)
	bool CalCulateEHIHI(float _DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsEHIHI = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentTime = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CoolTime = 30;

	UFUNCTION(BlueprintImplementableEvent)
	void EndEvent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isEnd = true;

	//UFUNCTION(BlueprintCallable)
	//void SetBoolArray(int32 _index, bool _bool);

	//UFUNCTION(BlueprintCallable)
	//int32 GetFalseIndex();

	//UFUNCTION(BlueprintCallable)
	//int32 GetTrueIndex();



	//UFUNCTION(BlueprintCallable)
	//TArray<class AC_Ample*> SwapAmplePos();

	//UFUNCTION(BlueprintCallable)
	//bool CheckCanSwap();

	//UFUNCTION(BlueprintCallable)
	//class AC_Ample* GetRandomAmple();


};
