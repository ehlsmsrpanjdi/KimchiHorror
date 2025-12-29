// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"  
#include "Sound/SoundBase.h"
#include "C_SoundDataTable.generated.h"

USTRUCT(BlueprintType)
struct FC_SoundDataTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	USoundBase* SoundAsset;
};
