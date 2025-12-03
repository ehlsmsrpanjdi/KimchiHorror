// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity/C_EntityBase.h"
#include "C_PatientNurse.generated.h"

/**
 *
 */
UCLASS()
class HORRORPROTOKIMCHI_API AC_PatientNurse : public AC_EntityBase
{
	GENERATED_BODY()

public:
	AC_PatientNurse();

protected:
	virtual void BeginPlay() override;

public:

	virtual void Tick(float _DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ACharacter* PatientActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ACharacter* DocActor;

	UPROPERTY()
	class AAIController* AIController;


	UFUNCTION(BlueprintCallable)
	void Chase(ACharacter* _target, float _Radius, float _Distance, float _waitTime);

	UFUNCTION(BlueprintCallable)
	float CalculateDistance(ACharacter* _Target);


public:
	UFUNCTION(BlueprintCallable)
	void SetWaitTime(float _WaitTime);

	UFUNCTION(BlueprintCallable)
	bool WaitFunction(float _DeltaTime);


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float currentTime = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float waitTime = 0.f;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 sequenceIndex = 0;

};
