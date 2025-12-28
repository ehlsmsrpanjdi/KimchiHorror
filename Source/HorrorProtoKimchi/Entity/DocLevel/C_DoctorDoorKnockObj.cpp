// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/DocLevel/C_DoctorDoorKnockObj.h"

// Sets default values
AC_DoctorDoorKnockObj::AC_DoctorDoorKnockObj()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_DoctorDoorKnockObj::BeginPlay()
{
	Super::BeginPlay();

}

bool AC_DoctorDoorKnockObj::CalculateCoolTime(float _DeltaTime)
{
	CurrentCoolTime += _DeltaTime;
	if (CurrentCoolTime > CoolTime) {
		CurrentCoolTime -= CoolTime;
		return true;
	}
	return false;
}


