// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "C_TitlePlayerController.generated.h"

/**
 *
 */
UCLASS()
class HORRORPROTOKIMCHI_API AC_TitlePlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
};
