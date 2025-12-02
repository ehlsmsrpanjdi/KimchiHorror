// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HorrorProtoKimchiGameMode.generated.h"

/**
 *  Simple GameMode for a third person game
 */
UCLASS(abstract)
class AHorrorProtoKimchiGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	/** Constructor */
	AHorrorProtoKimchiGameMode();

public:
	UPROPERTY()
	float currentDelayTime;


	UFUNCTION(BlueprintCallable)
	void CalculateTime(float _Delaytime);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 minute;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 hour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 currentTime;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DayCount;
};



