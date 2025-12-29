// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/PuzzleLevel/C_Button.h"

// Sets default values
AC_Button::AC_Button()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AC_Button::ActiveAllEvent()
{
	OnAction.Broadcast();
}
