// Fill out your copyright notice in the Description page of Project Settings.


#include "C_QuestComponent.h"
#include "C_GameInstance.h"
#include "Data/C_QuestDataTable.h"
#include "Data/C_SoundDataTable.h"

// Sets default values for this component's properties
UC_QuestComponent::UC_QuestComponent()
{
}




bool UC_QuestComponent::CheckQuestLine(FName _CurrentSelectedQuestObjName)
{
	if (CurrentQuestLine == _CurrentSelectedQuestObjName) {
		return true;
	}
	return false;
}

void UC_QuestComponent::ExecuteQuest_Implementation(FName _CurrentQuestLine)
{
}

void UC_QuestComponent::SetNextQuestLine(FName _NextQuestLine)
{
	CurrentQuestLine = _NextQuestLine;
}



