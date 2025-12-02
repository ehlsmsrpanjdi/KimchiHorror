// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/Stage_1/C_StrangePatient.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


AC_StrangePatient::AC_StrangePatient()
{
	PrimaryActorTick.bCanEverTick = true;

	// AI Controller 자동 빙의
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// 속도 설정
	GetCharacterMovement()->MaxWalkSpeed = ChaseSpeed;
}

void AC_StrangePatient::BeginPlay()
{
	Super::BeginPlay();

	// AI Controller 가져오기
	AIController = Cast<AAIController>(GetController());

	// 플레이어 캐릭터 가져오기
	PlayerCharacter = GetWorld()->GetFirstPlayerController()->GetCharacter();
}

void AC_StrangePatient::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (nullptr == PlayerCharacter || nullptr == AIController)
	{
		return;
	}

	// 플레이어가 바라보는지 확인
	if (IsPlayerLookingAt())
	{
		// 바라보면 멈춤
		AIController->StopMovement();
	}
	else
	{
		// 안 바라보면 이동
		AIController->MoveToActor(
			PlayerCharacter,
			50.0f,  // 수용 반경
			true,   // StopOnOverlap
			true,   // UsePathfinding
			true,   // CanStrafe
			nullptr,
			true    // AllowPartialPath
		);
	}
}

bool AC_StrangePatient::IsPlayerLookingAt()
{
	if (nullptr == PlayerCharacter)
	{
		return false;
	}

	// 플레이어 Forward Vector
	FVector PlayerForward = PlayerCharacter->GetActorForwardVector();

	// 플레이어 → Entity 방향
	FVector PlayerToEntity = (GetActorLocation() - PlayerCharacter->GetActorLocation()).GetSafeNormal();

	// Dot Product로 각도 계산
	float DotProduct = FVector::DotProduct(PlayerForward, PlayerToEntity);
	float Angle = FMath::Acos(DotProduct) * (180.0f / PI);

	// 시야각 내에 있으면 true
	return Angle < ViewAngle;
}