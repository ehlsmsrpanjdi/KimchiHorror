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

	FVector playerLocation = TargetActor->GetActorLocation();
	FVector myLocation = OwnerEntity->GetActorLocation();

	FVector DirVec = playerLocation - myLocation;

	FVector Dir = DirVec.GetSafeNormal();
	FVector Start = myLocation;

	float Distance = FVector::Distance(playerLocation, myLocation);

	// Multi Trace (여러 객체를 한 번에 검출)
	{
		TArray<FHitResult> Hits;

		// ObjectType 설정 (원하는 타입만 잡기)
		FCollisionObjectQueryParams ObjParams;
		ObjParams.AddObjectTypesToQuery(ECC_Pawn);

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(OwnerEntity);

		bool bHit = GetWorld()->LineTraceMultiByObjectType(
			Hits,
			Start,
			Start + Dir * 100,
			ObjParams,
			Params
		);

		if (bHit)
		{
			for (auto& Hit : Hits)
			{
				DrawDebugLine(GetWorld(), Start, Hit.ImpactPoint, FColor::Red, false, 1.f, 0, 2.f);
				if (Hit.GetActor() == TargetActor) {
					OwnerEntity->JumpScare();
				}
			}
		}
	}
}

void UC_DoubtChase::StateEnd()
{
}
