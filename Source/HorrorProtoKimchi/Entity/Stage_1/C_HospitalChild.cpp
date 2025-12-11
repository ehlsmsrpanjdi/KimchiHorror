// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/Stage_1/C_HospitalChild.h"
#include "HorrorProtoKimchiCharacter.h"
#include <Kismet/GameplayStatics.h>
#include "Debug/LogHelper.h"

void AC_HospitalChild::BeginPlay()
{
	Super::BeginPlay();


	ACharacter* PlayerChar = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	Player = Cast<AHorrorProtoKimchiCharacter>(PlayerChar);
}

void AC_HospitalChild::LayPlayer()
{
	FVector playerLocation = Player->GetActorLocation();
	FVector myLocation = GetActorLocation();

	FVector DirVec = playerLocation - myLocation;
	FVector Dir = DirVec.GetSafeNormal();

	FVector Start = myLocation;
	float Distance = FVector::Distance(playerLocation, myLocation);

	// ====================================================================
	// ① Single Trace (빨간색) - 벽에 막히는 레이
	// ====================================================================
	{
		FHitResult Hit;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

		FVector End = Start + Dir * FindPlayerDistance;

		bool bHit = GetWorld()->LineTraceSingleByChannel(
			Hit,
			Start,
			End,
			ECC_Visibility,
			Params
		);

		if (bHit)
		{
			// 디버그 라인 & Impact 지점 표시
			DrawDebugLine(GetWorld(), Start, Hit.ImpactPoint, FColor::Red, false, 1.f, 0, 2.f);
			DrawDebugPoint(GetWorld(), Hit.ImpactPoint, 12.f, FColor::Red, false, 1.f);

			if (Distance < 1000 && Hit.GetActor() == Player)
			{
				isFind = true;
			}
		}
		else
		{
			DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.f, 0, 2.f);
		}
	}

	// ====================================================================
	// ② MultiTrace (초록색) - 맞닿은 모든 오브젝트 체크
	// ====================================================================
	{
		TArray<FHitResult> Hits;

		FCollisionObjectQueryParams ObjParams;
		ObjParams.AddObjectTypesToQuery(ECC_Pawn);

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

		FVector End = Start + Dir * AttackPlayerDistance;

		bool bHit = GetWorld()->LineTraceMultiByObjectType(
			Hits,
			Start,
			End,
			ObjParams,
			Params
		);

		// MultiTrace 디버그 라인 그리기
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1.f, 0, 1.f);

		if (bHit)
		{
			for (auto& Hit : Hits)
			{
				DrawDebugPoint(GetWorld(), Hit.ImpactPoint, 10.f, FColor::Green, false, 1.f);
				LogHelper::Log(GetWorld(), Hit.GetActor()->GetFullName());
				if (Hit.GetActor() == Player)
				{
					JumpScare();
				}
			}
		}
	}
}
