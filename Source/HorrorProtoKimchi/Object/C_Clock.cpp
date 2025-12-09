// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Clock.h"
#include "HorrorProtoKimchiGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ArrowComponent.h"

AC_Clock::AC_Clock()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(RootComponent);

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

	const float CurrentTime = gameMode->currentTime;

	int32 CurrentMinute = (int32)(CurrentTime / 60) % 60;

	// 1분 = 6도 (360도 / 60분)
	float MinuteAngle = CurrentMinute * 6.0f;


	int32 CurrentHour = (int32)(CurrentTime / 3600) % 12; // 12시간 기준

	// 1시간 = 30도 (360도 / 12시간)
	float HourAngle = CurrentHour * 30.0f;

	// 분에 따른 추가 회전 (시침은 분에 따라 조금씩 움직임)
	HourAngle += CurrentMinute * 0.5f; // 1분 = 0.5도


	if (nullptr != MinuteNiddle) {
		MinuteNiddle->SetRelativeRotation(FRotator(-MinuteAngle, 0, 0));
	}

	if (nullptr != HourNiddle) {
		HourNiddle->SetRelativeRotation(FRotator(-HourAngle, 0, 0));
	}




	//// GameMode 안에 float CurrentTime; 있다고 가정
	//const float CurrentTime = gameMode->currentTime;

	//// ───────────────────────
	////   시침 (CurrentTime / 3600)
	//// ───────────────────────

	//	const float HourValue = CurrentTime / 3600.f;
	//	const FRotator HourRot(0.f, -HourValue * 30.f, 0.f);

	//	if (HourNiddle)
	//	{
	//		HourNiddle->SetRelativeRotation(HourRot);
	//	}

	//// ───────────────────────
	////   분침 (CurrentTime / 60)
	//// ───────────────────────


	//	const float currentMinute = CurrentTime % 3600;

	//	const float MinuteValue = CurrentTime / 60.0f;
	//	const FRotator MinuteRot(0.f, -MinuteValue, 0.f);

	//	if (MinuteNiddle)
	//	{
	//		MinuteNiddle->SetRelativeRotation(MinuteRot);
	//	}
}