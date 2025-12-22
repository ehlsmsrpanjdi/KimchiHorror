// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_FaceMoodEnum.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class C_FaceMoodEnum : uint8
{
   Normal UMETA(DisplayName = "Normal"),
   Joy  UMETA(DisplayName = "Joy"),
   Anger      UMETA(DisplayName = "Anger"),
   MadLaugh      UMETA(DisplayName = "MadLaugh"),
   MadCloseEye UMETA(DisplayName = "MadCloseEye")
   
};

