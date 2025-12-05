// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Clock.h"
#include "HorrorProtoKimchiGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ArrowComponent.h"

AC_Clock::AC_Clock()
{
    PrimaryActorTick.bCanEverTick = true;
    MinuteNiddle = CreateDefaultSubobject<UArrowComponent>(TEXT("MinuteNiddle"));
    HourNiddle = CreateDefaultSubobject<UArrowComponent>(TEXT("HourNiddle"));
    MinuteNiddle->SetupAttachment(RootComponent);
    HourNiddle->SetupAttachment(RootComponent);
}

void AC_Clock::BeginPlay()
{
    Super::BeginPlay();

    // 게임모드 가져오기
    if (AGameModeBase* GM = UGameplayStatics::GetGameMode(this))
    {
        gameMode = Cast<AHorrorProtoKimchiGameMode>(GM);
    }

    if (!gameMode)
    {
        UE_LOG(LogTemp, Warning, TEXT("AC_Clock: GameMode cast failed!"));
    }
}

void AC_Clock::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!gameMode)
        return;

    // GameMode 안에 float CurrentTime; 있다고 가정
    const float CurrentTime = gameMode->currentTime;

    // ───────────────────────
    //   시침 (CurrentTime / 3600)
    // ───────────────────────

    {
        const float HourValue = CurrentTime / 3600.0f;
        const FRotator HourRot(0.f, -HourValue, 0.f);

        if (HourNiddle)
        {
            HourNiddle->SetRelativeRotation(HourRot);
        }
    }

    // ───────────────────────
    //   분침 (CurrentTime / 60)
    // ───────────────────────

    {
        const float MinuteValue = CurrentTime / 60.0f;
        const FRotator MinuteRot(0.f, -MinuteValue, 0.f);

        if (MinuteNiddle)
        {
            MinuteNiddle->SetRelativeRotation(MinuteRot);
        }
    }
}