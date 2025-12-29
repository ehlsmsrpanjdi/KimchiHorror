// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_Button.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonClick);


UCLASS()
class HORRORPROTOKIMCHI_API AC_Button : public AActor
{
	GENERATED_BODY()

public:

	// 함수 포인터 역할
	UPROPERTY(BlueprintAssignable)
	FOnButtonClick OnAction;


	// Sets default values for this actor's properties

	AC_Button();



	UFUNCTION(BlueprintCallable)
	void ActiveAllEvent();
};
