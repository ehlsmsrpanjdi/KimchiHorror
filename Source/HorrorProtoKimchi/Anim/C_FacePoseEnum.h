// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_FacePoseEnum.generated.h"


UENUM(BlueprintType)
enum class C_FacePoseEnum : uint8
{
    Idle        UMETA(DisplayName = "Idle"),
    Talk       UMETA(DisplayName = "Talk"),
    Smile  UMETA(DisplayName = "Smlie"),
    Anger      UMETA(DisplayName = "Anger"),
    Strange      UMETA(DisplayName = "Strange"),
};
