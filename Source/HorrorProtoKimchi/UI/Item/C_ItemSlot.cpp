// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Item/C_ItemSlot.h"
#include "Debug/LogHelper.h"
#include "UI/Item/C_InventoryUI.h"
#include "UI/C_UIManager.h"

void UC_ItemSlot::OnclickSlot()
{
	UC_UIManager* uiManager = UC_UIManager::GetUIManager(GetWorld());

	UUserWidget* gainUI = uiManager->GetUI(UC_InventoryUI::StaticClass());

	UC_InventoryUI* inventory = Cast<UC_InventoryUI>(gainUI);

	if(IsValid(inventory) == false)
	{
		return;
	}

	int32 slotIndex = inventory->GetItemSlotNumber(this);

	FString Msg = FString::Printf(TEXT("ItemSlot Number is = %d"), slotIndex);

	LogHelper::PrintOnly(this, Msg);
	 
}
