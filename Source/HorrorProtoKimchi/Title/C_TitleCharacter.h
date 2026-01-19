// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C_TitleCharacter.generated.h"

UCLASS()
class HORRORPROTOKIMCHI_API AC_TitleCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_TitleCharacter();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* FollowCamera;

	// 원뿔 반경(각도). 예: 20도
	UPROPERTY(EditAnywhere, Category = "TitleLook")
	float ConeAngleDeg = 10.f;

	// 화면 비율에 따라 Pitch가 과하게 느껴질 수 있어서 분리
	UPROPERTY(EditAnywhere, Category = "TitleLook")
	float PitchWeight = 0.7f;   // 1이면 동일, 0.7이면 Pitch 덜 움직임

	// 부드럽게 따라가는 속도
	UPROPERTY(EditAnywhere, Category = "TitleLook")
	float InterpSpeed = 8.f;

	// 중앙 근처는 흔들림 줄이는 데드존(선택)
	UPROPERTY(EditAnywhere, Category = "TitleLook")
	float DeadZoneNormalized = 0.05f; // 0~1 (0.05면 중심 5% 영역은 0 취급)

private:
	FRotator BaseBoomRot;

	// -1..1 정규화 + 데드존 적용
	float ApplyDeadZone(float v) const;

};
