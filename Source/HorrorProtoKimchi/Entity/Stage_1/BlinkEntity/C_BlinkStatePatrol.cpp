// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/Stage_1/BlinkEntity/C_BlinkStatePatrol.h"
#include "Entity/Stage_1/C_BlinkEntity.h"
#include "Components/SplineComponent.h"

void UC_BlinkStatePatrol::StateStart()
{
	Super::StateStart();

	if (OwnerEntity == nullptr) {
		AC_EntityBase* baseEntity = GetMachineOwner();
		OwnerEntity = Cast<AC_BlinkEntity>(baseEntity);
	}

	// 현재 위치 기준으로 시작
	Spline = OwnerEntity->GetSpline();
	if (Spline)
	{
		FVector CurrentLocation = OwnerEntity->GetActorLocation();
		float InputKey = Spline->FindInputKeyClosestToWorldLocation(CurrentLocation);
		CurrentDistance = Spline->GetDistanceAlongSplineAtSplineInputKey(InputKey);
	}
	else
	{
		CurrentDistance = 0.0f;
	}
}

void UC_BlinkStatePatrol::StateUpdate(float _DeltaTime)
{
	Super::StateUpdate(_DeltaTime);

	if (nullptr == OwnerEntity) {
		return;
	}

	// Spline 컴포넌트 가져오기
	if (nullptr == Spline) {
		return;
	}

	// 거리 증가
	CurrentDistance += MoveSpeed * _DeltaTime;

	// 스플라인 전체 길이
	float SplineLength = Spline->GetSplineLength();

	// 루프 처리
	if (CurrentDistance >= SplineLength)
	{
		if (bLoop) {
			CurrentDistance = 0.0f; // 처음으로
		}
		else {
			CurrentDistance = SplineLength; // 끝에서 정지
		}
	}

	// 스플라인 위치 계산
	FVector NewLocation = Spline->GetLocationAtDistanceAlongSpline(
		CurrentDistance,
		ESplineCoordinateSpace::World
	);

	// 회전 계산 (진행 방향)
	FRotator NewRotation = Spline->GetRotationAtDistanceAlongSpline(
		CurrentDistance,
		ESplineCoordinateSpace::World
	);

	// 액터 이동
	OwnerEntity->SetActorLocation(NewLocation);
	OwnerEntity->SetActorRotation(NewRotation);
}

void UC_BlinkStatePatrol::StateEnd()
{
	Super::StateEnd();
}
