// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "C_DrugLevelGameState.generated.h"

/**
 *
 */
UCLASS()
class HORRORPROTOKIMCHI_API AC_DrugLevelGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	FLinearColor GetColor();

	UFUNCTION(BlueprintCallable)
	bool Correct();

	UFUNCTION(BlueprintCallable)
	bool InCorrect();

	UFUNCTION(BlueprintCallable)
	bool MoveAgain();

	UFUNCTION(BlueprintCallable)
	bool CheckIndex(int32 _Index);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 LifeCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 LightIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Color")
	FLinearColor RedColor = FLinearColor(1.f, 0.f, 0.f, 1.f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Color")
	FLinearColor YellowColor = FLinearColor(1.f, 1.f, 0.f, 1.f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Color")
	FLinearColor WhiteColor = FLinearColor(1.f, 1.f, 1.f, 1.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bPrevCorrect = false;
};
