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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

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
};
