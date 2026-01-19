// Fill out your copyright notice in the Description page of Project Settings.


#include "Title/C_TitleCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AC_TitleCharacter::AC_TitleCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// 타이틀용: 캐릭터가 컨트롤 회전에 따라 돌지 않게
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	// 이동 필요 없으면 아예 꺼도 됩니다(선택)
	if (UCharacterMovementComponent* Move = GetCharacterMovement())
	{
		Move->DisableMovement();
	}

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.f;
	CameraBoom->bUsePawnControlRotation = false;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

void AC_TitleCharacter::BeginPlay()
{
	Super::BeginPlay();
	BaseBoomRot = CameraBoom->GetRelativeRotation();
}

float AC_TitleCharacter::ApplyDeadZone(float v) const
{
	const float a = FMath::Abs(v);
	if (a < DeadZoneNormalized) return 0.f;

	// 데드존 밖은 0..1로 다시 리맵(부드럽게)
	const float sign = FMath::Sign(v);
	const float t = (a - DeadZoneNormalized) / (1.f - DeadZoneNormalized);
	return sign * FMath::Clamp(t, 0.f, 1.f);
}

void AC_TitleCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC) return;

	float MouseX, MouseY;
	if (!PC->GetMousePosition(MouseX, MouseY)) return;

	int32 SizeX, SizeY;
	PC->GetViewportSize(SizeX, SizeY);
	if (SizeX <= 0 || SizeY <= 0) return;

	// 0..1 -> -1..1 (화면 중심 0)
	float nx = (MouseX / (float)SizeX) * 2.f - 1.f;
	float ny = (MouseY / (float)SizeY) * 2.f - 1.f;

	nx = ApplyDeadZone(nx);
	ny = ApplyDeadZone(ny);

	// Pitch는 위로 올리면 보통 -pitch가 자연스러움
	float yaw = nx * ConeAngleDeg;
	float pitch = (-ny) * ConeAngleDeg * PitchWeight;

	// "원뿔(원형) 제한": (yaw, pitch) 벡터 길이가 ConeAngleDeg를 넘으면 줄이기
	const float len = FMath::Sqrt(yaw * yaw + pitch * pitch);
	if (len > ConeAngleDeg && len > KINDA_SMALL_NUMBER)
	{
		const float s = ConeAngleDeg / len;
		yaw *= s;
		pitch *= s;
	}

	const FRotator TargetRot = BaseBoomRot + FRotator(pitch, yaw, 0.f);
	const FRotator NewRot = FMath::RInterpTo(CameraBoom->GetRelativeRotation(), TargetRot, DeltaSeconds, InterpSpeed);
	CameraBoom->SetRelativeRotation(NewRot);
}