// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity/C_StateBase.h"
#include "C_BlinkStateChase.generated.h"

/**
 * 
 */
UCLASS()
class HORRORPROTOKIMCHI_API UC_BlinkStateChase : public UC_StateBase
{
	GENERATED_BODY()
	
public:
	virtual void StateStart() override;
	virtual void StateUpdate(float _DeltaTime) override;
	virtual void StateEnd() override;

protected:
	UPROPERTY()
	class AC_BlinkEntity* OwnerEntity;
	UPROPERTY()
	AActor* TargetActor;

	class AAIController* AIController;
};
