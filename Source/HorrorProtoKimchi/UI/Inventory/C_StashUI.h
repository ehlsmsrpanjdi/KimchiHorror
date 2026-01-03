// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/C_ItemData.h"
#include "Blueprint/UserWidget.h"
#include "C_StashUI.generated.h"

/**
 * 
 */
UCLASS()
class HORRORPROTOKIMCHI_API UC_StashUI : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, Category = "Stash")
	TArray<TObjectPtr<UC_ItemData>> KHItems;

	UFUNCTION(BlueprintCallable, Category = "Stash")
	void KHAddItem(UC_ItemData* ItemData);

	UFUNCTION(BlueprintCallable, Category = "Stash")
	UC_ItemData* KHGetItem(int32 Index) const;

	UFUNCTION(BlueprintCallable, Category = "Stash")
	void KHSortItems();

	UFUNCTION(BlueprintCallable, Category = "Stash")
	void KHEmptyItems();
};
