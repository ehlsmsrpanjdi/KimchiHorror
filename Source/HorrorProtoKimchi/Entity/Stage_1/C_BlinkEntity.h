// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity/C_EntityBase.h"
#include "C_BlinkEntity.generated.h"


class USplineComponent;
class UBoxComponent;

/**
 *
 */
UCLASS()
class HORRORPROTOKIMCHI_API AC_BlinkEntity : public AC_EntityBase
{
	GENERATED_BODY()

public:
	AC_BlinkEntity();

protected:
	virtual void StateInit() override;

	virtual void BeginPlay() override;

public:
	virtual void Tick(float _DeltaTime) override;

protected:

	/** 스플라인 경로 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blink", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USplineComponent> Spline;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blink", meta = (AllowPrivateAccess = "true"))
	bool MoveClock = true;

public:
	FORCEINLINE USplineComponent* GetSpline() const { return Spline; }

	UFUNCTION(BlueprintCallable)
	void StartMachine();
};