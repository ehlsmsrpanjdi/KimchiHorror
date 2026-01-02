// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_NumberPad.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNumberPadClear);


UCLASS()
class HORRORPROTOKIMCHI_API AC_NumberPad : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AC_NumberPad();

public:
	// 함수 포인터 역할
	UPROPERTY(BlueprintAssignable)
	FOnNumberPadClear OnAction;

	UFUNCTION(BlueprintCallable)
	void ActiveAllEvent();


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* DirectionComponent;

	UFUNCTION(BlueprintCallable)
	void CalculateDirection();

	FVector FowardDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> NumberArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AActor>> NumberAssetArray;

	UFUNCTION(BlueprintCallable)
	FVector CalculateCurrentPos(float _Scale = 1.f);

	UFUNCTION(BlueprintCallable)
	void ClearNumber();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> AnswerValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> CurrentArrayValue;

	UFUNCTION(BlueprintCallable)
	bool CheckAnswer();
};
