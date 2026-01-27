// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "C_DiaryDataTable.generated.h"


/**
 * 
 */
USTRUCT(BlueprintType)
struct FC_DiaryDataTable : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FText DiaryTitle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FText DiaryContents;
};
