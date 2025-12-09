// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "C_StateMachine.h"
#include "C_StateBase.generated.h"

/**
 * 
 */
class AC_EntityBase;

UCLASS()
class HORRORPROTOKIMCHI_API UC_StateBase : public UObject
{
	GENERATED_BODY()

public:
	virtual void StateStart();
	virtual void StateUpdate(float _DeltaTime);
	virtual void StateEnd();

	void SetMachine(UC_StateMachine* _Machine);


	UPROPERTY()
	UC_StateMachine* mainMachine;

protected:
	class AC_EntityBase* GetMachineOwner();
};
