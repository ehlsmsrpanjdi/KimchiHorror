// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"  
#include "C_RoomSign.generated.h"
/**
 *
 */


USTRUCT(BlueprintType)
struct FC_RoomSign : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText RoomSignText;
};
