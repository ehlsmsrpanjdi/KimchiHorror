// Fill out your copyright notice in the Description page of Project Settings.


#include "Debug/LogHelper.h"

void LogHelper::Log(UObject* WorldContext, const FString& Msg, float Duration, const FLinearColor Color)
{
    if (!WorldContext) return;

    // UE_LOG 출력 (경고 색)
    UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);

    // 화면 출력 (블루프린트 PrintString 기능)
    UKismetSystemLibrary::PrintString(
        WorldContext,
        Msg,
        true,     // 화면
        true,     // 로그
        Color,
        Duration
    );
}

void LogHelper::LogOnly(const FString& Msg)
{
    UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);
}

void LogHelper::PrintOnly(UObject* WorldContext, const FString& Msg, float Duration, const FLinearColor Color)
{
    if (!WorldContext) return;

    UKismetSystemLibrary::PrintString(
        WorldContext,
        Msg,
        true,     // 화면
        false,    // 로그 X
        Color,
        Duration
    );
}