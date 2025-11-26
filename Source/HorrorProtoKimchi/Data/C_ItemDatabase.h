// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "../Item/C_ItemData.h"
#include "C_ItemDatabase.generated.h"

/**
 * 
 */
UCLASS()
class HORRORPROTOKIMCHI_API UC_ItemDatabase : public UDataAsset
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemDatabase")
    TArray<UC_ItemData*> Items;

    /** ID로 아이템 검색 */
    UFUNCTION(BlueprintCallable)
    UC_ItemData* FindItemByID(int32 ItemID) const
    {
        for (UC_ItemData* Item : Items)
        {
            if (Item && Item->ItemID == ItemID)
                return Item;
        }
        return nullptr;
    }
};