// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_InventoryUI.generated.h"

/**
 * 
 */
UCLASS()
class HORRORPROTOKIMCHI_API UC_InventoryUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	int32 GetItemSlotNumber(class UC_ItemSlot* _Slot);

private:
	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* GridPanel;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", Meta = (AllowPrivateAccess = "true"))
	TArray<class UC_ItemSlot*> InventorySlotUIs;
};
