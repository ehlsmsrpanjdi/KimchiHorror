// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"  
#include "Sound/SoundBase.h"
#include "C_QuestDataTable.generated.h"

USTRUCT(BlueprintType)
struct FC_QuestDataTable : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	FName CurrentQuestID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	FName NextQuestID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	FText QuestDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	FName SoundID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	FText DialogueText;
};
