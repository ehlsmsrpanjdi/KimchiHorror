#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "C_KimchiHelper.generated.h"

UCLASS()
class HORRORPROTOKIMCHI_API UC_KimchiHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/* =========================
	 * Line Trace
	 * ========================= */

	 /** LineTrace (Actor → Actor) */
	UFUNCTION(BlueprintCallable, Category = "Kimchi|Trace")
	static FHitResult LineTraceActorToActor(
		const AActor* FromActor,
		const AActor* ToActor,
		bool bDrawDebug = false
	);

	/** LineTrace (Location → Location) */
	UFUNCTION(
		BlueprintCallable,
		Category = "Kimchi|Trace",
		meta = (WorldContext = "WorldContextObject")
	)
	static FHitResult LineTraceLocationToLocation(
		const UObject* WorldContextObject,
		const FVector& From,
		const FVector& To,
		bool bDrawDebug = false
	);

	/* =========================
	 * Navigation
	 * ========================= */

	 /** Navigation Move (Actor → Actor) */
	UFUNCTION(BlueprintCallable, Category = "Kimchi|Navigation")
	static bool MoveToActorAndCheckArrival(
		APawn* Pawn,
		AActor* TargetActor,
		float AcceptableRadius = 50.f,
		bool Log = false
	);

	/** Navigation Move (Actor → Location) */
	UFUNCTION(BlueprintCallable, Category = "Kimchi|Navigation")
	static bool MoveToLocationAndCheckArrival(
		APawn* Pawn,
		const FVector& TargetLocation,
		float AcceptableRadius = 50.f,
		bool Log = false
	);

	UFUNCTION(BlueprintCallable, Category = "Kimchi|Navigation")
	static bool IsNavigationAvailable(const UObject* WorldContextObject, const FVector& Point, FVector& OutNavLocation, float boxSize, bool Debug = false);

	UFUNCTION(BlueprintCallable, Category = "Kimchi|CheckDistance")
	static float GetSpeedRateByDistance(
		AActor* OwnerActor,
		AActor* TargetActor,
		float MinDistance,      // 이 거리 이하면 최소 속도
		float MaxDistance,      // 이 거리 이상이면 최대 속도
		float MinSpeedRate,     // 최소 속도 비율 (예: 0.3 = 30%)
		float MaxSpeedRate      // 최대 속도 비율 (예: 1.0 = 100%)
	);

	UFUNCTION(BlueprintCallable, Category = "Kimchi|Random")
	static int32 GetRandomInteger(int32 _start, int32 _end);
};
