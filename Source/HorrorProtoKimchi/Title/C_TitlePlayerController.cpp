// Fill out your copyright notice in the Description page of Project Settings.


#include "Title/C_TitlePlayerController.h"

void AC_TitlePlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;

	// 타이틀은 UI 클릭이 중요하므로 GameAndUI 권장
	FInputModeGameAndUI Mode;
	Mode.SetHideCursorDuringCapture(false);
	Mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock); // 필요시 LockAlways로 변경
	SetInputMode(Mode);
}