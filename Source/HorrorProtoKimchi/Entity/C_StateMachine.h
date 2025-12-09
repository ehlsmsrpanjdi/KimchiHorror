// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "C_StateEnum.h"
#include "C_StateMachine.generated.h"

class AC_EntityBase;
class UC_StateBase;
/**
 * 
 */
UCLASS()
class HORRORPROTOKIMCHI_API UC_StateMachine : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	C_StateEnum currentStateEnum;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UC_StateBase* currentState;

	void StateUpdate(float _DelaTime);
	void StateChange(C_StateEnum _state);


	void SetOwner(AC_EntityBase* _Owner);

	void AddState(C_StateEnum _Enum, UC_StateBase* _State);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AC_EntityBase* OwnerEntity;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TMap<C_StateEnum, UC_StateBase*> stateMap;

};
