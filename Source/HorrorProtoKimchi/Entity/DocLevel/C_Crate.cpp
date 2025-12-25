// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/DocLevel/C_Crate.h"
#include "Debug/LogHelper.h"

// Sets default values
AC_Crate::AC_Crate()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	isPutArray.SetNum(4);
}

// Called when the game starts or when spawned
void AC_Crate::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AC_Crate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_Crate::SetBoolArray(int32 _index, bool _bool)
{
	if (_index >= isPutArray.Num()) {
		LogHelper::PrintOnly(this, "Index Override");
		return;
	}
	isPutArray[_index] = _bool;
}

int32 AC_Crate::GetTrueIndex()
{
	for (int i = 0; i < isPutArray.Num(); ++i) {
		if (isPutArray[i] == false) {
			return i;
		}
	}
	return -1;
}

