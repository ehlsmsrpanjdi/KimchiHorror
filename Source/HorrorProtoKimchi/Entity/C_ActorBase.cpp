// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/C_ActorBase.h"
#include "HorrorProtoKimchiGameMode.h"

// Sets default values
AC_ActorBase::AC_ActorBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_ActorBase::BeginPlay()
{
	Super::BeginPlay();
	if (AHorrorProtoKimchiGameMode* GM = Cast<AHorrorProtoKimchiGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GM->OnHourChanged.AddDynamic(this, &AC_ActorBase::InvokeTimeEvent);
	}

}

// Called every frame
void AC_ActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AC_ActorBase::InvokeTimeEvent_Implementation(int32 _TimeValue) {
	if (_TimeValue == 6) {

	}
}

void AC_ActorBase::OnHourChange(int32 hour)
{
	InvokeTimeEvent(hour);
}

void AC_ActorBase::SetActiveFalse()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
}

void AC_ActorBase::SetActiveTrue()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetActorTickEnabled(true);
}
