// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/Stage_1/BlinkEntity/C_BlinkStateReturn.h"
#include "Entity/Stage_1/C_BlinkEntity.h"
#include "Entity/C_StateEnum.h"
#include "Components/SplineComponent.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"

void UC_BlinkStateReturn::StateStart()
{
	Super::StateStart();

	if (OwnerEntity == nullptr) {
		AC_EntityBase* baseEntity = GetMachineOwner();
		OwnerEntity = Cast<AC_BlinkEntity>(baseEntity);
	}

	if (nullptr == OwnerEntity) {
		return;
	}

	// AI Controller 가져오기
	AIController = Cast<AAIController>(OwnerEntity->GetController());
	if (nullptr == AIController)
	{
		UE_LOG(LogTemp, Error, TEXT("No AI Controller in Return State!"));
		return;
	}

	// Spline 가져오기
	USplineComponent* Spline = OwnerEntity->GetSpline();
	if (nullptr == Spline)
	{
		UE_LOG(LogTemp, Error, TEXT("No Spline in Return State!"));
		mainMachine->StateChange(C_StateEnum::Idle);
		return;
	}

	// 현재 위치에서 가장 가까운 Spline 지점 찾기
	FVector CurrentLocation = OwnerEntity->GetActorLocation();
	float InputKey = Spline->FindInputKeyClosestToWorldLocation(CurrentLocation);
	ReturnDistance = Spline->GetDistanceAlongSplineAtSplineInputKey(InputKey);

	// 돌아갈 위치 계산
	ReturnLocation = Spline->GetLocationAtDistanceAlongSpline(
		ReturnDistance,
		ESplineCoordinateSpace::World
	);

	// 이동 시작
	AIController->MoveToLocation(
		ReturnLocation,
		AcceptanceRadius,
		true,  // StopOnOverlap
		true,  // UsePathfinding
		true,  // ProjectDestinationToNavigation
		true,  // CanStrafe
		nullptr, // Filter Class
		true   // AllowPartialPath
	);
}

void UC_BlinkStateReturn::StateUpdate(float _DeltaTime)
{
	Super::StateUpdate(_DeltaTime);

	if (nullptr == OwnerEntity || nullptr == AIController)
	{
		return;
	}

	float Distance = FVector::Dist(
		OwnerEntity->GetActorLocation(),
		ReturnLocation
	);

	if (Distance < AcceptanceRadius)
	{
		// 정확한 위치/회전 설정
		OwnerEntity->SetActorLocation(ReturnLocation);

		USplineComponent* Spline = OwnerEntity->GetSpline();
		if (Spline)
		{
			FRotator TargetRotation = Spline->GetRotationAtDistanceAlongSpline(
				ReturnDistance,
				ESplineCoordinateSpace::World
			);
			OwnerEntity->SetActorRotation(TargetRotation);
		}

		mainMachine->StateChange(C_StateEnum::Idle);
		return;
	}

	EPathFollowingStatus::Type Status = AIController->GetMoveStatus();
	if (Status == EPathFollowingStatus::Idle)
	{
		AIController->MoveToLocation(ReturnLocation, 10);
	}
}

void UC_BlinkStateReturn::StateEnd()
{
	Super::StateEnd();

	// 이동 중지
	if (AIController)
	{
		AIController->StopMovement();
	}

	UE_LOG(LogTemp, Warning, TEXT("Return State Ended"));
}