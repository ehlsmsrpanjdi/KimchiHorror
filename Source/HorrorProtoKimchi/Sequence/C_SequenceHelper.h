// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_SequenceHelper.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSequenceCallback);

UCLASS()
class HORRORPROTOKIMCHI_API AC_SequenceHelper : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_SequenceHelper();



	// 2. 블루프린트에서 함수 포인터처럼 쓸 변수
	UPROPERTY(BlueprintAssignable, Category = "Sequence")
	FOnSequenceCallback OnSequenceFinished;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void RunSequence();

	// 3. 실행 함수
	UFUNCTION(BlueprintCallable, Category = "Sequence")
	void ExecuteCallback();
};
