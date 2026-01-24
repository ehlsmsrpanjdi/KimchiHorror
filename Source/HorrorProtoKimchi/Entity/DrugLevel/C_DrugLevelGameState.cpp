// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/DrugLevel/C_DrugLevelGameState.h"
#include "Entity/DrugLevel/C_BlinkLight.h"

FLinearColor AC_DrugLevelGameState::GetColor() {
	switch (LifeCount)
	{
	case 0:
		return WhiteColor;
	case 1:
		return YellowColor;
	case 2:
		return RedColor;
	default:
		return WhiteColor;
	}
}

bool AC_DrugLevelGameState::Correct() {
	LifeCount = 0;
	bPrevCorrect = true;
	return true;
}

bool AC_DrugLevelGameState::InCorrect() {
	++LifeCount;
	bPrevCorrect = false;
	return false;
}

bool AC_DrugLevelGameState::MoveAgain()
{
	++LifeCount;
	return false;
}

bool AC_DrugLevelGameState::CheckIndex(int32 _Index) {
	if (LightIndex == _Index) {
		++LightIndex;
		Correct();
		return true;
	}
	InCorrect();
	return false;
}