// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Item/C_InventoryUI.h"
#include "Components/UniformGridPanel.h"
#include "UI/Item/C_ItemSlot.h"

void UC_InventoryUI::NativeConstruct()
{
	Super::NativeConstruct();

	InventorySlotUIs.Empty();

	int32 Count = GridPanel->GetChildrenCount();
	for (int32 i = 0; i < Count; i++)
	{
		UWidget* Child = GridPanel->GetChildAt(i);

		UC_ItemSlot* itemSlot = Cast<UC_ItemSlot>(Child);
		if (itemSlot)
		{
			InventorySlotUIs.Add(itemSlot);
		}
	}
}

int32 UC_InventoryUI::GetItemSlotNumber(UC_ItemSlot* _Slot)
{
	return InventorySlotUIs.Find(_Slot);
}
