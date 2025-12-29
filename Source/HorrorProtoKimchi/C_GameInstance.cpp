// Fill out your copyright notice in the Description page of Project Settings.


#include "C_GameInstance.h"

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
