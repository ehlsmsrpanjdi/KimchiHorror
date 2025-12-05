// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_ActorBase.generated.h"

UCLASS()
class HORRORPROTOKIMCHI_API AC_ActorBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AC_ActorBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void InvokeTimeEvent(int32 _TimeValue);
	virtual void InvokeTimeEvent_Implementation(int32 _TimeValue);

	UFUNCTION(BlueprintCallable)
	void OnHourChange(int32 hour);


	UFUNCTION(BlueprintCallable)
	void SetActiveFalse();

	UFUNCTION(BlueprintCallable)
	void SetActiveTrue();

};
