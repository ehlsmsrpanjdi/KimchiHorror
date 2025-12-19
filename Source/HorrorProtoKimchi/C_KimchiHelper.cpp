#include "C_KimchiHelper.h"
#include "AIController.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "Debug/LogHelper.h"


FHitResult UC_KimchiHelper::LineTraceActorToActor(
	const AActor* FromActor,
	const AActor* ToActor,
	bool bDrawDebug
)
{
	FHitResult HitResult;

	if (!FromActor || !ToActor)
	{
		return HitResult;
	}

	UWorld* World = FromActor->GetWorld();
	if (!World)
	{
		return HitResult;
	}

	FCollisionQueryParams Params;
	Params.bTraceComplex = false;
	Params.AddIgnoredActor(FromActor); // 자기 자신 무시

	const bool bHit = World->LineTraceSingleByChannel(
		HitResult,
		FromActor->GetActorLocation(),
		ToActor->GetActorLocation(),
		ECC_Pawn,
		Params
	);

	if (bDrawDebug)
	{
		// 맞은 Actor 정보 출력
		FString HitInfo;
		if (bHit)
		{
			AActor* HitActor = HitResult.GetActor();
			HitInfo = FString::Printf(TEXT("Hit: %s (Target: %s) Match: %s"),
				HitActor ? *HitActor->GetName() : TEXT("None"),
				*ToActor->GetName(),
				(HitActor == ToActor) ? TEXT("TRUE") : TEXT("FALSE")
			);
		}
		else
		{
			HitInfo = TEXT("No Hit");
		}

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Yellow, HitInfo);
		}

		// 시각적 디버그
		const bool bHitTarget = bHit && HitResult.GetActor() == ToActor;
		const FColor DebugColor = bHitTarget ? FColor::Green : FColor::Red;
		DrawDebugLine(
			World,
			FromActor->GetActorLocation(),
			ToActor->GetActorLocation(),
			DebugColor,
			false,
			1.0f,
			0,
			2.0f
		);

		// 히트 포인트 표시
		if (bHit)
		{
			DrawDebugSphere(
				World,
				HitResult.Location,
				10.f,
				12,
				FColor::Orange,
				false,
				1.0f
			);
		}
	}

	return HitResult;
}

FHitResult UC_KimchiHelper::LineTraceLocationToLocation(
	const UObject* WorldContextObject,
	const FVector& From,
	const FVector& To,
	bool bDrawDebug
)
{
	FHitResult HitResult;

	if (!WorldContextObject)
	{
		return HitResult; // 빈 HitResult 반환
	}

	UWorld* World = GEngine->GetWorldFromContextObject(
		WorldContextObject,
		EGetWorldErrorMode::ReturnNull
	);
	if (!World)
	{
		return HitResult; // 빈 HitResult 반환
	}

	FCollisionQueryParams Params;
	Params.bTraceComplex = false;
	// 자기 자신 Trace 방지
	if (const AActor* IgnoreActor = Cast<AActor>(WorldContextObject))
	{
		Params.AddIgnoredActor(IgnoreActor);
	}

	const bool bHit = World->LineTraceSingleByChannel(
		HitResult,
		From,
		To,
		ECC_Pawn,
		Params
	);

	if (bDrawDebug)
	{
		const FColor DebugColor = bHit ? FColor::Red : FColor::Green;
		DrawDebugLine(
			World,
			From,
			To,
			DebugColor,
			false,
			1.0f,
			0,
			2.0f
		);
	}

	return HitResult;
}

bool UC_KimchiHelper::MoveToActorAndCheckArrival(
	APawn* Pawn,
	AActor* TargetActor,
	float AcceptableRadius,
	bool Log
)
{
	if (!Pawn || !TargetActor)
	{
		return false;
	}
	AAIController* AICon = Cast<AAIController>(Pawn->GetController());

	FVector TargetLocation = TargetActor->GetActorLocation();
	if (!AICon)
	{
		return false;
	}
	const float Distance = FVector::Dist(
		Pawn->GetActorLocation(),
		TargetLocation
	);

	if (Log)
	{
		LogHelper::PrintOnly(
			Pawn,
			FString::Printf(TEXT("Distance: %.1f / Acceptable: %.1f"), Distance, AcceptableRadius),
			0.1f,
			Distance <= AcceptableRadius ? FLinearColor::Green : FLinearColor::Red
		);
	}

	// 이미 도착했으면 true
	if (Distance <= AcceptableRadius)
	{
		return true;
	}

	// 도착하지 않았으면 이동 명령
	const float MoveRadius = FMath::Max(0.f, AcceptableRadius - 50.f);
	AICon->MoveToLocation(TargetLocation, MoveRadius);
	return false;
}

bool UC_KimchiHelper::MoveToLocationAndCheckArrival(
	APawn* Pawn,
	const FVector& TargetLocation,
	float AcceptableRadius,
	bool Log
)
{
	if (!Pawn)
	{
		return false;
	}
	AAIController* AICon = Cast<AAIController>(Pawn->GetController());
	if (!AICon)
	{
		return false;
	}
	const float Distance = FVector::Dist(
		Pawn->GetActorLocation(),
		TargetLocation
	);

	if (Log)
	{
		LogHelper::PrintOnly(
			Pawn,
			FString::Printf(TEXT("Distance: %.1f / Acceptable: %.1f"), Distance, AcceptableRadius),
			0.1f,
			Distance <= AcceptableRadius ? FLinearColor::Green : FLinearColor::Red
		);
	}

	// 이미 도착했으면 true
	if (Distance <= AcceptableRadius)
	{
		return true;
	}

	// 도착하지 않았으면 이동 명령
	const float MoveRadius = FMath::Max(0.f, AcceptableRadius - 50.f);
	AICon->MoveToLocation(TargetLocation, MoveRadius);
	return false;
}

bool UC_KimchiHelper::IsNavigationAvailable(const UObject* WorldContextObject, const FVector& Point, FVector& OutNavLocation, float boxSize, bool Debug)
{
	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(WorldContextObject->GetWorld());

	if (!NavSys)
	{
		return false;
	}

	FNavLocation ResultLocation;
	FVector QueryExtent(boxSize, boxSize, boxSize);

	// ProjectPointToNavigation의 반환값이 성공/실패를 나타냄
	bool bHasNavigation = NavSys->ProjectPointToNavigation(
		Point,
		ResultLocation,
		QueryExtent
	);

	if (Debug == true) {
		if (bHasNavigation)
		{
			// 네비게이션이 있으면 투영된 위치 반환
			OutNavLocation = ResultLocation.Location;
			UE_LOG(LogTemp, Log, TEXT("Navigation found at: %s"), *OutNavLocation.ToString());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No navigation at point: %s"), *Point.ToString());
		}
	}

	return bHasNavigation;
}
