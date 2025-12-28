// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_BlinkLight.generated.h"

UCLASS()
class HORRORPROTOKIMCHI_API AC_BlinkLight : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AC_BlinkLight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	float GetFlickerNoise(float MinIntensity, float MaxIntensity, float Speed);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsBlinking = false;
};
