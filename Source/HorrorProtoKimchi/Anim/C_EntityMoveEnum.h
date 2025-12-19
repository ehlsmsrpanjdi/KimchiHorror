// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_EntityMoveEnum.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class C_EntityMoveEnum : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Walk UMETA(DisplayName = "Walk"),
	Run UMETA(DisplayName = "Run"),
	Dance  UMETA(DisplayName = "Dance")
};
