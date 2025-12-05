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
	AGameModeBase* gamemodeBase = GetWorld()->GetAuthGameMode();
	AHorrorProtoKimchiGameMode* CastGameMode = Cast<AHorrorProtoKimchiGameMode>(gamemodeBase);

	CastGameMode->AddTimeActor(this);

}

// Called every frame
void AC_ActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AC_ActorBase::InvokeTimeEvent_Implementation(int32 _TimeValue) {

}

