// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "C_ItemData.generated.h"

/**
 * 
 */
UCLASS()
class HORRORPROTOKIMCHI_API UC_ItemData : public UObject
{
	GENERATED_BODY()
	
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ItemName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UTexture2D* ItemIcon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ItemID;

    // 나중에 오버라이드해서 효과 구현
    UFUNCTION(BlueprintCallable)
    virtual void UseItem(class AActor* User);
};
