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
	UFUNCTION(BlueprintCallable)
	int32 GetHour();


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
	int32 currentHour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DayCount;

	UFUNCTION(BlueprintCallable)
	void SetHour();

	UFUNCTION(BlueprintCallable)
	void AddTimeActor(class AC_ActorBase* _timeActor);

	UFUNCTION(BlueprintCallable)
	void AddTimeCharacter(class AC_EntityBase* _timeActor);

	UFUNCTION(BlueprintCallable)
	void OnTimeFunctionOnCharacters(int32 _TimeValue);

	UFUNCTION(BlueprintCallable)
	void OnTimeFunctionOnActors(int32 _TimeValue);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<class AC_ActorBase*> TimeActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<class AC_EntityBase*> TimeCharacters;
};



