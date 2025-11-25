// C_Inventory.cpp
#include "Item/C_Inventory.h"

UC_Inventory::UC_Inventory()
{
	// 10Ä­ nullptr·Î ÃÊ±âÈ­
	Items.Init(nullptr, MaxSlots);
}

bool UC_Inventory::AddItem(UC_ItemData* NewItem)
{
	if (!NewItem)
	{
		UE_LOG(LogTemp, Warning, TEXT("Trying to add null item"));
		return false;
	}

	// ºó ½½·Ô Ã£±â
	for (int32 i = 0; i < MaxSlots; i++)
	{
		if (Items[i] == nullptr)
		{
			Items[i] = NewItem;
			UE_LOG(LogTemp, Log, TEXT("Item added to slot %d: %s"), i, *NewItem->ItemName);
			return true;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Inventory is full!"));
	return false;
}

void UC_Inventory::RemoveItemAtSlot(int32 SlotIndex)
{
	if (!Items.IsValidIndex(SlotIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid slot index: %d"), SlotIndex);
		return;
	}

	if (Items[SlotIndex] != nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("Item removed from slot %d"), SlotIndex);
		Items[SlotIndex] = nullptr;
	}
}

void UC_Inventory::UseItemAtSlot(int32 SlotIndex, AActor* User)
{
	if (!Items.IsValidIndex(SlotIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid slot index: %d"), SlotIndex);
		return;
	}

	if (Items[SlotIndex] != nullptr)
	{
		Items[SlotIndex]->UseItem(User);
		RemoveItemAtSlot(SlotIndex);
	}
}

UC_ItemData* UC_Inventory::GetItemAtSlot(int32 SlotIndex) const
{
	if (Items.IsValidIndex(SlotIndex))
	{
		return Items[SlotIndex];
	}

	return nullptr;
}

int32 UC_Inventory::GetEmptySlotCount() const
{
	int32 EmptyCount = 0;
	for (UC_ItemData* Item : Items)
	{
		if (Item == nullptr)
		{
			EmptyCount++;
		}
	}
	return EmptyCount;
}