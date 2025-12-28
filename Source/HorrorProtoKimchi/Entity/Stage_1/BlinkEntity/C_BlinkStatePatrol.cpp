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

	Spline = OwnerEntity->GetSpline();
	if (Spline)
	{
		FVector CurrentLocation = OwnerEntity->GetActorLocation();

		// 가장 가까운 Spline Point 찾기
		int32 NumPoints = Spline->GetNumberOfSplinePoints();
		int32 ClosestPointIndex = 0;
		float MinDistance = FLT_MAX;

		for (int32 i = 0; i < NumPoints; i++)
		{
			FVector PointLocation = Spline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World);
			float Distance = FVector::Dist(CurrentLocation, PointLocation);

			if (Distance < MinDistance)
			{
				MinDistance = Distance;
				ClosestPointIndex = i;
			}
		}

		// 가장 가까운 Spline Point의 거리로 설정
		CurrentDistance = Spline->GetDistanceAlongSplineAtSplinePoint(ClosestPointIndex);

		// 해당 위치로 이동
		FVector SplineLocation = Spline->GetLocationAtSplinePoint(ClosestPointIndex, ESplineCoordinateSpace::World);
		FRotator SplineRotation = Spline->GetRotationAtSplinePoint(ClosestPointIndex, ESplineCoordinateSpace::World);

		OwnerEntity->SetActorLocation(SplineLocation);
		OwnerEntity->SetActorRotation(SplineRotation);
	}
	else
	{
		CurrentDistance = 0.0f;
	}
}

void UC_BlinkStatePatrol::StateUpdate(float _DeltaTime)
{
	Super::StateUpdate(_DeltaTime);
	if (OwnerEntity->MoveClock == true) {
		MoveClock(_DeltaTime);
	}
	else {
		MoveNotClock(_DeltaTime);
	}
}

void UC_BlinkStatePatrol::StateEnd()
{
	Super::StateEnd();
}

void UC_BlinkStatePatrol::MoveClock(float _DeltaTime)
{
	if (nullptr == OwnerEntity) {
		return;
	}
	// Spline 컴포넌트 가져오기
	if (nullptr == Spline) {
		Spline = OwnerEntity->GetSpline();
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

void UC_BlinkStatePatrol::MoveNotClock(float _DeltaTime)
{
	if (nullptr == OwnerEntity) {
		return;
	}
	// Spline 컴포넌트 가져오기
	if (nullptr == Spline) {
		Spline = OwnerEntity->GetSpline();
		return;
	}
	// 거리 감소 (역방향)
	CurrentDistance -= MoveSpeed * _DeltaTime;
	// 스플라인 전체 길이
	float SplineLength = Spline->GetSplineLength();
	// 루프 처리
	if (CurrentDistance <= 0.0f)
	{
		if (bLoop) {
			CurrentDistance = SplineLength; // 끝에서 다시 시작
		}
		else {
			CurrentDistance = 0.0f; // 처음에서 정지
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