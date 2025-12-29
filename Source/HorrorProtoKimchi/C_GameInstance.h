// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Data/C_ItemDatabase.h"
#include "Data/C_QuestDataTable.h"
#include "Data/C_SoundDataTable.h"
#include "C_GameInstance.generated.h"

/**
 *
 */
UCLASS()
class HORRORPROTOKIMCHI_API UC_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemSystem")
	UC_ItemDatabase* ItemDatabase;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DataTable")
	UDataTable* SoundDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DataTable")
	UDataTable* QuestDataTable;

	UFUNCTION(BlueprintCallable)
	FC_QuestDataTable GetQuestData(FName _QuestData);

	UFUNCTION(BlueprintCallable)
	FC_SoundDataTable GetSoundData(FName _SoundData);
};
