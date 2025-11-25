// C_Inventory.h
#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "C_ItemData.h"
#include "C_Inventory.generated.h"

UCLASS(BlueprintType)
class HORRORPROTOKIMCHI_API UC_Inventory : public UObject
{
	GENERATED_BODY()

public:
	UC_Inventory();

	UPROPERTY(BlueprintReadOnly)
	TArray<UC_ItemData*> Items;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MaxSlots = 10;

	// 아이템 추가 (빈 슬롯에)
	UFUNCTION(BlueprintCallable)
	bool AddItem(UC_ItemData* NewItem);

	// 특정 슬롯의 아이템 제거
	UFUNCTION(BlueprintCallable)
	void RemoveItemAtSlot(int32 SlotIndex);

	// 특정 슬롯의 아이템 사용 (사용 후 제거)
	UFUNCTION(BlueprintCallable)
	void UseItemAtSlot(int32 SlotIndex, AActor* User);

	// 특정 슬롯의 아이템 가져오기
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UC_ItemData* GetItemAtSlot(int32 SlotIndex) const;

	// 빈 슬롯 개수
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 GetEmptySlotCount() const;
};