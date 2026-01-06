// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_SyringeBox.generated.h"

UCLASS()
class HORRORPROTOKIMCHI_API AC_SyringeBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_SyringeBox();

public:	
	UFUNCTION(BlueprintCallable)
	void InteractionEvent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> SyringeClass;
};
