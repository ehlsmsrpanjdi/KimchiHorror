// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/C_EntityBase.h"
#include "Entity/C_StateMachine.h"
#include "HorrorProtoKimchiGameMode.h"

// Sets default values
AC_EntityBase::AC_EntityBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_EntityBase::BeginPlay()
{
	Super::BeginPlay();
	entityStateMachine = NewObject<UC_StateMachine>(this);
	entityStateMachine->SetOwner(this);

	AGameModeBase* gamemodeBase = GetWorld()->GetAuthGameMode();
	AHorrorProtoKimchiGameMode* CastGameMode = Cast<AHorrorProtoKimchiGameMode>(gamemodeBase);

	CastGameMode->AddTimeCharacter(this);

	StateInit();
}

// Called every frame
void AC_EntityBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (nullptr != entityStateMachine) {
		entityStateMachine->StateUpdate(DeltaTime);
	}
}

// Called to bind functionality to input
void AC_EntityBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AC_EntityBase::StateInit()
{
}

void AC_EntityBase::ChangeState(C_StateEnum _stateEnum)
{
	currentStateEnum = _stateEnum;
	if (nullptr != entityStateMachine) {
		entityStateMachine->StateChange(_stateEnum);
	}
}

void AC_EntityBase::AddState(C_StateEnum _Enum, UC_StateBase* _BaseState)
{
	entityStateMachine->AddState(_Enum, _BaseState);
}

void AC_EntityBase::InvokeTimeEvent_Implementation(int32 _TimeValue)
{
}

void AC_EntityBase::SetActiveFalse()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
}

void AC_EntityBase::SetActiveTrue()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetActorTickEnabled(true);
}

