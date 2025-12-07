// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/C_DoubtChase.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "Entity/C_StateBase.h"
#include "Entity/C_EntityBase.h"
#include "HorrorProtoKimchiCharacter.h"
#include "Kismet/GameplayStatics.h"

UC_DoubtChase::UC_DoubtChase()
{
}

void UC_DoubtChase::StateStart()
{
	Super::StateStart();
	if (OwnerEntity == nullptr) {
		AC_EntityBase* baseEntity = GetMachineOwner();
		OwnerEntity = Cast<AC_EntityBase>(baseEntity);
	}

	if (OwnerEntity != nullptr) {
		TargetActor = Cast<AHorrorProtoKimchiCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	}

	AIController = Cast<AAIController>(OwnerEntity->GetController());
	if (nullptr == AIController)
	{
		UE_LOG(LogTemp, Error, TEXT("No AI Controller!"));
		return;
	}
}

void UC_DoubtChase::StateUpdate(float _DeltaTime)
{
	Super::StateUpdate(_DeltaTime);

	if (nullptr == OwnerEntity || nullptr == TargetActor)
	{
		return;
	}

	// NavMesh 따라 이동
	AIController->MoveToActor(
		TargetActor,
		50.0f, // 수용 반경 (이 거리까지 도달하면 성공)
		true,  // StopOnOverlap
		true,  // UsePathfinding
		true,  // CanStrafe
		nullptr, // Filter Class
		true   // AllowPartialPath
	);
}

void UC_DoubtChase::StateEnd()
{
}
