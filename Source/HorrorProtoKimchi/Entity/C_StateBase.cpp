// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/C_StateBase.h"
#include "Entity/C_StateMachine.h"
#include "Entity/C_EntityBase.h"

void UC_StateBase::StateStart() {

}

void UC_StateBase::StateUpdate(float _DeltaTime) {

}

void UC_StateBase::StateEnd() {

}

void UC_StateBase::SetMachine(UC_StateMachine* _Machine)
{
	mainMachine = _Machine;
}

AC_EntityBase* UC_StateBase::GetMachineOwner()
{
	return mainMachine->OwnerEntity;
}
