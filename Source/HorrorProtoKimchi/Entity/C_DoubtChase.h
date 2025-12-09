// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity/C_StateBase.h"
#include "C_DoubtChase.generated.h"

/**
 * 
 */

UCLASS()
class HORRORPROTOKIMCHI_API UC_DoubtChase : public UC_StateBase
{
	GENERATED_BODY()

public:
	UC_DoubtChase();

public:
	virtual void StateStart() override;
	virtual void StateUpdate(float _DeltaTime) override;
	virtual void StateEnd() override;


	UPROPERTY()
	class AC_EntityBase* OwnerEntity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* TargetActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AAIController* AIController;

};
