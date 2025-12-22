// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/Stage_1/BlinkEntity/C_BlinkStateChase.h"
#include "Entity/Stage_1/C_BlinkEntity.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"

void UC_BlinkStateChase::StateStart()
{
	//Super::StateStart();

	//if (OwnerEntity == nullptr) {
	//	AC_EntityBase* baseEntity = GetMachineOwner();
	//	OwnerEntity = Cast<AC_BlinkEntity>(baseEntity);
	//}

	//if (OwnerEntity != nullptr) {
	//	TargetActor = OwnerEntity->GetTargetActor();
	//}

	//AIController = Cast<AAIController>(OwnerEntity->GetController());
	//if (nullptr == AIController)
	//{
	//	UE_LOG(LogTemp, Error, TEXT("No AI Controller!"));
	//	return;
	//}
}

void UC_BlinkStateChase::StateUpdate(float _DeltaTime)
{
	//Super::StateUpdate(_DeltaTime);

	//if (nullptr == OwnerEntity || nullptr == TargetActor)
	//{
	//	mainMachine->StateChange(C_StateEnum::Idle);
	//	return;
	//}
	//if (AIController == nullptr) {
	//	return;
	//}
	//// NavMesh 따라 이동
	//AIController->MoveToActor(
	//	TargetActor,
	//	50.0f, // 수용 반경 (이 거리까지 도달하면 성공)
	//	true,  // StopOnOverlap
	//	true,  // UsePathfinding
	//	true,  // CanStrafe
	//	nullptr, // Filter Class
	//	true   // AllowPartialPath
	//);
}

void UC_BlinkStateChase::StateEnd()
{
	//Super::StateEnd();

	//// 이동 중지
	//if (OwnerEntity)
	//{
	//	AC_BlinkEntity* BlinkEntity = Cast<AC_BlinkEntity>(OwnerEntity);
	//	if (BlinkEntity)
	//	{
	//		if (AIController)
	//		{
	//			AIController->StopMovement();
	//		}
	//	}
	//}

	//TargetActor = nullptr;
}