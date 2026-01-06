// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_DocEntitySpawner.generated.h"

UCLASS()
class HORRORPROTOKIMCHI_API AC_DocEntitySpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AC_DocEntitySpawner();


public:

	UFUNCTION(BlueprintCallable)
	TSubclassOf<ACharacter> GetRandomCharacter();

	UFUNCTION(BlueprintCallable)
	class UArrowComponent* GetRandomPoint();

	UFUNCTION(BlueprintCallable)
	void SetupPointPos(float _Distance);

	UFUNCTION(BlueprintCallable)
	void ResetSpawnPointBool(int _index);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 currentSelectedIndex;

	UFUNCTION(BlueprintCallable)
	AActor* SpawnEntity();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* Point_1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* Point_2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* Point_3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* Point_4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* Point_5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* Point_6;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UArrowComponent*> SpawnPointArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<bool> IsSpawnArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<ACharacter>> EntityArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ACharacter> Phase_2Entity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ACharacter> Phase_3Entity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PhaseCoolTime = 120.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PhaseCurrentTime = 0.0f;

	UFUNCTION(BlueprintCallable)
	bool CalculateTime(float _DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float currentTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CoolTime = 20;

	UFUNCTION(BlueprintImplementableEvent)
	void EndEvent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isEnd = true;
};
