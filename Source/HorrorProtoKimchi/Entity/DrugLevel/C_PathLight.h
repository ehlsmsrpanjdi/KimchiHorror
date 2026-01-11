// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_PathLight.generated.h"

UCLASS()
class HORRORPROTOKIMCHI_API AC_PathLight : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AC_PathLight();


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsOverlaped = false;

};
