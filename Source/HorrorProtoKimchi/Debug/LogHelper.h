// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetSystemLibrary.h"

/**
 * 
 */
class HORRORPROTOKIMCHI_API LogHelper
{
public:

    //	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blink", meta = (AllowPrivateAccess = "true"))


    // 화면 + 로그 둘 다
    static void Log(UObject* WorldContext, const FString& Msg, float Duration = 2.f, const FLinearColor Color = FLinearColor::Yellow);

    // 로그만 출력
    static void LogOnly(const FString& Msg);

    // 화면만 출력 (PrintString 동일)
    static void PrintOnly(UObject* WorldContext, const FString& Msg, float Duration = 2.f, const FLinearColor Color = FLinearColor::White);
};