// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity/C_StateBase.h"
#include "C_BlinkStateReturn.generated.h"

/**
 * 
 */
UCLASS()
class HORRORPROTOKIMCHI_API UC_BlinkStateReturn : public UC_StateBase
{
	GENERATED_BODY()
	
public:
	virtual void StateStart() override;
	virtual void StateUpdate(float _DeltaTime) override;
	virtual void StateEnd() override;

private:
	UPROPERTY()
	class AC_BlinkEntity* OwnerEntity;

	UPROPERTY()
	class AAIController* AIController;

	/** Spline으로 돌아갈 목표 지점 */
	FVector ReturnLocation;

	/** 돌아갈 Spline 거리 */
	float ReturnDistance;

	/** 도착 판정 거리 */
	float AcceptanceRadius = 150.0f;
};
