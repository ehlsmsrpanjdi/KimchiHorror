// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/C_StashUI.h"



void UC_StashUI::KHAddItem(UC_ItemData* ItemData)
{
	if (!ItemData)
	{
		return;
	}

	KHItems.Add(ItemData);
}

UC_ItemData* UC_StashUI::KHGetItem(int32 Index) const
{
	if (!KHItems.IsValidIndex(Index))
	{
		return nullptr;
	}

	return KHItems[Index].Get();
}

void UC_StashUI::KHSortItems()
{
	TArray<TObjectPtr<UC_ItemData>> NewItems;
	NewItems.Reserve(KHItems.Num());

	for (const TObjectPtr<UC_ItemData>& Item : KHItems)
	{
		if (Item)
		{
			NewItems.Add(Item);
		}
	}

	KHItems = MoveTemp(NewItems);
}