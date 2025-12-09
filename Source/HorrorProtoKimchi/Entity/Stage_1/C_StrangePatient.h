// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity/C_EntityBase.h"
#include "C_StrangePatient.generated.h"

/**
 * 
 */
UCLASS()
class HORRORPROTOKIMCHI_API AC_StrangePatient : public AC_EntityBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	AC_StrangePatient();
	virtual void Tick(float _Deltatime) override;

public:
	UPROPERTY()
	ACharacter* PlayerCharacter;

	UPROPERTY()
	class AAIController* AIController;

	/** 플레이어 시야각 (도) */
	UPROPERTY(EditAnywhere, Category = "AI")
	float ViewAngle = 45.0f;

	/** 추격 속도 */
	UPROPERTY(EditAnywhere, Category = "AI")
	float ChaseSpeed = 300.0f;

	/** 플레이어가 바라보는지 확인 */
	bool IsPlayerLookingAt();
};
