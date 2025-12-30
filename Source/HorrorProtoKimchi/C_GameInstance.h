// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Data/C_ItemDatabase.h"
#include "Data/C_QuestDataTable.h"
#include "Data/C_SoundDataTable.h"
#include "Sound/SoundClass.h"
#include "C_GameInstance.generated.h"

/**
 *
 */
UCLASS()
class HORRORPROTOKIMCHI_API UC_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	//DataTable
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


public:
	//SaveData
	UFUNCTION(BlueprintCallable)
	void SaveGame(const FName& _CurrentLevelName);

	UFUNCTION(BlueprintCallable)
	class UC_SaveGame* GetSaveData();

	UFUNCTION(BlueprintCallable)
	bool DeleteSaveData();

	UFUNCTION(BlueprintCallable)
	FName GetSavedLevelName();

	UFUNCTION(BlueprintCallable)
	FName GetCurrentLevelName();

	UFUNCTION(BlueprintCallable)
	const FString& GetDefaultSlotName();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName CurrentLevelName;

	const FString SlotName = "DEFAULT";

public:
	//SoundData
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
	USoundClass* MasterSoundClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
	USoundClass* SFXSoundClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
	USoundClass* BGMSoundClass;

	UFUNCTION(BlueprintCallable, Category = "Audio")
	void SetMasterVolume(float Volume);

	UFUNCTION(BlueprintCallable, Category = "Audio")
	void SetSFXVolume(float Volume);

	UFUNCTION(BlueprintCallable, Category = "Audio")
	void SetBGMVolume(float Volume);

public:
	//MouseSensetive

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MouseSensetive = 2.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Brightness = 2.2f;

	UFUNCTION(BlueprintCallable)
	void SetMouseSensetive(float Value);

	// QuestComponent.h
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ExecuteBrightness(float Value);

	// C++에서 기본 구현 제공
	virtual void ExecuteBrightness_Implementation(float Value);

	UFUNCTION(BlueprintCallable)
	void PlayerBeginPlay();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DayCount = 1;


	UFUNCTION(BlueprintCallable)
	void SetCurrentLevelName();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ReSpawnPlayer();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ReSpawnInit();

	virtual void ReSpawnPlayer_Implementation();

	virtual void ReSpawnInit_Implementation();
};
