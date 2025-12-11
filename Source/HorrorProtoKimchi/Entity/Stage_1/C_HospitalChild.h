// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity/C_EntityBase.h"
#include "C_HospitalChild.generated.h"

/**
 *
 */
UCLASS()
class HORRORPROTOKIMCHI_API AC_HospitalChild : public AC_EntityBase
{
	GENERATED_BODY()


protected:
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable)
	void LayPlayer();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isFind = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AHorrorProtoKimchiCharacter* Player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FindPlayerDistance = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackPlayerDistance = 50;
};
