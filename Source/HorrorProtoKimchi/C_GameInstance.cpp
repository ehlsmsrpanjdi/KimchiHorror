// Fill out your copyright notice in the Description page of Project Settings.


#include "C_GameInstance.h"
#include "C_SaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerInput.h"

FC_QuestDataTable UC_GameInstance::GetQuestData(FName _QuestData)
{
	if (!QuestDataTable) {
		return FC_QuestDataTable();
	}

	FC_QuestDataTable* QuestData = QuestDataTable->FindRow<FC_QuestDataTable>(_QuestData, TEXT(""));

	if (QuestData == nullptr) {
		return FC_QuestDataTable();
	}

	else {
		return *QuestData;
	}
}


FC_SoundDataTable UC_GameInstance::GetSoundData(FName _SoundData)
{
	if (!SoundDataTable) {
		return FC_SoundDataTable();
	}

	FC_SoundDataTable* SoundData = SoundDataTable->FindRow<FC_SoundDataTable>(_SoundData, TEXT(""));

	if (SoundData == nullptr) {
		return FC_SoundDataTable();
	}

	else {
		return *SoundData;
	}
}

FC_FocusItemData UC_GameInstance::GetItemDiscriptionData(FName _ItemData)
{
	if (!ItemDiscriptionDataTable) {
		return FC_FocusItemData();
	}
	FC_FocusItemData* ItemData = ItemDiscriptionDataTable->FindRow<FC_FocusItemData>(_ItemData, TEXT(""));

	if (ItemData == nullptr) {
		return FC_FocusItemData();
	}
	else {
		return *ItemData;
	}
}


void UC_GameInstance::SaveGame()
{
	UC_SaveGame* SaveGameData = Cast<UC_SaveGame>(
		UGameplayStatics::CreateSaveGameObject(UC_SaveGame::StaticClass())
	);

	if (!SaveGameData) {
		return;
	}

	SaveGameData->DayCount = DayCount;
	UGameplayStatics::SaveGameToSlot(SaveGameData, SlotName, 0);
}

UC_SaveGame* UC_GameInstance::GetSaveData()
{
	UC_SaveGame* LoadedData = Cast<UC_SaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
	if (!LoadedData) {
		return nullptr;
	}
	else {
		return LoadedData;
	}
}

bool UC_GameInstance::DeleteSaveData()
{
	return UGameplayStatics::DeleteGameInSlot(SlotName, 0);
}


//게임 시작할때 및 load했을때의 레벨
int32 UC_GameInstance::GetSavedDayCount()
{
	UC_SaveGame* LoadedData = GetSaveData();
	if (LoadedData == nullptr) {
		return 1;
	}
	else {
		return LoadedData->DayCount;
	}
}


//죽었을때 사용 용도의 세이브레벨
FName UC_GameInstance::GetCurrentLevelName()
{
	return CurrentLevelName;
}

const FString& UC_GameInstance::GetDefaultSlotName()
{
	return SlotName;
}

void UC_GameInstance::SetMasterVolume(float Volume)
{
	if (MasterSoundClass)
	{
		MasterSoundClass->Properties.Volume = FMath::Clamp(Volume, 0.0f, 1.0f);
	}
}

void UC_GameInstance::SetSFXVolume(float Volume)
{
	if (SFXSoundClass)
	{
		SFXSoundClass->Properties.Volume = FMath::Clamp(Volume, 0.0f, 1.0f);
	}
}

void UC_GameInstance::SetBGMVolume(float Volume)
{
	if (BGMSoundClass)
	{
		BGMSoundClass->Properties.Volume = FMath::Clamp(Volume, 0.0f, 1.0f);
	}
}

void UC_GameInstance::SetMouseSensetive(float Value)
{
	MouseSensetive = FMath::Clamp(Value, 0.5f, 5.f);
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC && PC->PlayerInput)
	{
		PC->PlayerInput->SetMouseSensitivity(MouseSensetive);
	}
}

void UC_GameInstance::ExecuteBrightness_Implementation(float Value)
{
}

void UC_GameInstance::PlayerBeginPlay()
{
	SetMouseSensetive(MouseSensetive);
	ExecuteBrightness(Brightness);
}

void UC_GameInstance::SetCurrentLevelName()
{
	CurrentLevelName = FName(*UGameplayStatics::GetCurrentLevelName(GetWorld()));
}

void UC_GameInstance::ReSpawnPlayer_Implementation()
{
}

void UC_GameInstance::ReSpawnInit_Implementation()
{
}
