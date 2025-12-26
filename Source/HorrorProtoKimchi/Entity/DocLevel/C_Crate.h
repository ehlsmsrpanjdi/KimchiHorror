// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_Crate.generated.h"

UCLASS()
class HORRORPROTOKIMCHI_API AC_Crate : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AC_Crate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<bool> isPutArray;

	UFUNCTION(BlueprintCallable)
	void SetBoolArray(int32 _index, bool _bool);

	UFUNCTION(BlueprintCallable)
	int32 GetFalseIndex();

	UFUNCTION(BlueprintCallable)
	int32 GetTrueIndex();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> AmplesArray;

	UFUNCTION(BlueprintCallable)
	TArray<AActor*> SwapAmplePos();

	UFUNCTION(BlueprintCallable)
	bool CheckCanSwap();

	UFUNCTION(BlueprintCallable)
	AActor* GetRandomAmple();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AC_Crate* OtherCrate;
};
