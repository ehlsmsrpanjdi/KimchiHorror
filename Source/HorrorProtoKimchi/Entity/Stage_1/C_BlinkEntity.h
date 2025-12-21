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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blink", meta = (AllowPrivateAccess = "true"))
	AActor* TargetActor;

	/** 플레이어 감지용 콜라이더 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shape")
	UBoxComponent* DetectBox;

	/** 플레이어 감지 해제용 콜라이더 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shape")
	UBoxComponent* LoseBox;

	/** 플레이어가 DetectBox 에 들어왔을 때 */
	UFUNCTION(BlueprintCallable)
	void OnPlayerDetect(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	/** 플레이어가 DetectBox 에서 나갔을 때 */
	UFUNCTION(BlueprintCallable)
	void OnPlayerLose(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);

	//getter
public:
	FORCEINLINE USplineComponent* GetSpline() const { return Spline; }

	FORCEINLINE AActor* GetTargetActor() const {
		return TargetActor;
	}

};