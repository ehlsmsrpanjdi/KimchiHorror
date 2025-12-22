// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/Stage_1/C_BlinkEntity.h"
#include "Components/SplineComponent.h"
#include "Components/BoxComponent.h"
#include "Entity/C_StateEnum.h"
#include "Entity/Stage_1/BlinkEntity/C_BlinkStatePatrol.h"
#include "Entity/Stage_1/BlinkEntity/C_BlinkStateChase.h"
#include "Entity/Stage_1/BlinkEntity/C_BlinkStateReturn.h"
#include "Entity/C_StateMachine.h"
#include "AIController.h"

AC_BlinkEntity::AC_BlinkEntity()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AC_BlinkEntity::BeginPlay()
{
	Super::BeginPlay();

	ChangeState(C_StateEnum::Idle);
}

void AC_BlinkEntity::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AC_BlinkEntity::StateInit()
{
	UC_BlinkStatePatrol* PatrolState = NewObject<UC_BlinkStatePatrol>(this);

	AddState(C_StateEnum::Idle, PatrolState);
}
