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


};
