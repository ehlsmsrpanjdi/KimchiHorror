// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity/C_StateBase.h"
#include "C_BlinkStatePatrol.generated.h"

/**
 *
 */
UCLASS()
class HORRORPROTOKIMCHI_API UC_BlinkStatePatrol : public UC_StateBase
{
	GENERATED_BODY()

public:
	virtual void StateStart() override;
	virtual void StateUpdate(float _DeltaTime) override;
	virtual void StateEnd() override;

private:
	void MoveClock(float _DeltaTime);

	void MoveNotClock(float _DeltaTime);

	
	/** 현재 스플라인 거리 */
	float CurrentDistance;

	/** 이동 속도 */
	UPROPERTY(EditAnywhere)
	float MoveSpeed = 300.0f;

	/** 루프 여부 */
	UPROPERTY(EditAnywhere)
	bool bLoop = true;

	UPROPERTY()
	class AC_BlinkEntity* OwnerEntity;

	UPROPERTY()
	class USplineComponent* Spline;
};
