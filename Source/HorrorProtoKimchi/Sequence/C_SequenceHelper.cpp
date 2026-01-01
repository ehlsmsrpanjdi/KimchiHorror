// Fill out your copyright notice in the Description page of Project Settings.


#include "Sequence/C_SequenceHelper.h"

// Sets default values
AC_SequenceHelper::AC_SequenceHelper()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}


void AC_SequenceHelper::ExecuteCallback()
{
	OnSequenceFinished.Broadcast();
}
