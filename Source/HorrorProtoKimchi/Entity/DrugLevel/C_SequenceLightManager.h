// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_BlinkLight.h"
#include "GameFramework/Actor.h"
#include "C_SequenceLightManager.generated.h"

UCLASS()
class HORRORPROTOKIMCHI_API AC_SequenceLightManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AC_SequenceLightManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AC_BlinkLight*> SequenceLightArray;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CoolTime = 3.f;


	UFUNCTION(BlueprintCallable)
	void CalculateSequenceTime(float _DeltaTime);


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 currentIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 maxIndex;
};
