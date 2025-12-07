// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_StateEnum.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class C_StateEnum : uint8
{
    Idle        UMETA(DisplayName = "Idle"),
    Chase       UMETA(DisplayName = "Chase"),
    DoubtChase  UMETA(DisplayName = "DoubtChase"),
    Return      UMETA(DisplayName = "Return"),
    Attack      UMETA(DisplayName = "Attack"),
};
