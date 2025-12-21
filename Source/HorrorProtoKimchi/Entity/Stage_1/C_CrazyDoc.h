// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity/C_EntityBase.h"
#include "C_CrazyDoc.generated.h"

/**
 *
 */
UCLASS()
class HORRORPROTOKIMCHI_API AC_CrazyDoc : public AC_EntityBase
{
	GENERATED_BODY()

public:
	AC_CrazyDoc();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	class AAIController* AIController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	class UBoxComponent* DetectionBox;

	// 플레이어 추적 함수
	UFUNCTION(BlueprintCallable)
	void ChasePlayer();

	// Overlap 이벤트 함수들
	UFUNCTION(BlueprintCallable)
	void OnPlayerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void OnPlayerExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void CallPlayer();
	virtual void CallPlayer_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ChaseTalk();
	virtual void ChaseTalk_Implementation();


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float delayTime = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float currentTime = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 answerCount = 0;

public:
	UFUNCTION(BlueprintCallable)
	void GetRandomItem();

	UFUNCTION(BlueprintCallable)
	bool ReceiveItem(AActor* Obj);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<bool> isFind;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> Items;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* selectedObj;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//bool mesBool;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//bool forcepsBool;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//bool scissorsBool;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class ACharacter* TargetPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bIsChasing = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool IsNotice = false;
};