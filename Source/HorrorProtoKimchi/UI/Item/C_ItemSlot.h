// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_ItemSlot.generated.h"

/**
 * 
 */
UCLASS()
class HORRORPROTOKIMCHI_API UC_ItemSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	void OnclickSlot();
};
