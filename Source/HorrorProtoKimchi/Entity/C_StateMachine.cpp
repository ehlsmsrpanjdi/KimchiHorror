// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/C_StateMachine.h"
#include "Entity/C_StateBase.h"
#include "Entity/C_EntityBase.h"
#include "../Debug/LogHelper.h"

void UC_StateMachine::StateUpdate(float _DelaTime)
{
	if (nullptr == currentState) {
		return;
	}
	currentState->StateUpdate(_DelaTime);
}

void UC_StateMachine::StateChange(C_StateEnum _state)
{
	if (nullptr != currentState) {
		currentState->StateEnd();
	}

	UC_StateBase** findState = stateMap.Find(_state);

	if (nullptr == findState) {
		LogHelper::PrintOnly(this, TEXT("state is Null"));
		return;
	}

	currentState = *findState;
	currentState->StateStart();
	currentStateEnum = _state;
}

void UC_StateMachine::SetOwner(AC_EntityBase* _Owner)
{
	OwnerEntity = _Owner;
}

void UC_StateMachine::AddState(C_StateEnum _Enum, UC_StateBase* _State) {
	stateMap.Add(_Enum, _State);
	_State->SetMachine(this);
}
