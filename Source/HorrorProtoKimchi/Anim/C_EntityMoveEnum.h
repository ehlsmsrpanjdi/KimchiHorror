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
	LookDown UMETA(DisplayName = "LookDown"),
	MadStand UMETA(DisplayName = "MadStand"),
	Run UMETA(DisplayName = "Run"),
	Dance  UMETA(DisplayName = "Dance"),
	CatWalk UMETA(DisplayName = "CatWalk"),
	LeftTurn UMETA(DisplayName = "LeftTurn"),
	RightTurn UMETA(DisplayName = "RightTurn"),
	WalkLeftTurn UMETA(DisplayName = "WalkLeftTurn"),
	WalkRightTurn UMETA(DisplayName = "WalkRightTurn"),
	BackWalk UMETA(DisplayName = "BackWalk"),
	Talk1 UMETA(DisplayName = "Talk1"),
	Talk2 UMETA(DisplayName = "Talk2"),
	Talk3 UMETA(DisplayName = "Talk3"),
	Yelling  UMETA(DisplayName = "Yelling"),
	NinjaRun UMETA(DisplayName = "NinjaRun"),
	MadSit UMETA(DisplayName = "MadSit"),
	MadLie UMETA(DisplayName = "MadLie")

};
