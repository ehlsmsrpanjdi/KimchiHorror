// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HorrorProtoKimchiGameMode.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHourChanged, int32, NewHour);


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
	//현재 시간 반환받기
	UFUNCTION(BlueprintCallable)
	int32 GetHour();
	//시간을 인자만큼 증가시키기
	UFUNCTION(BlueprintCallable)
	void AddHour(int32 time);
	//시간을 인자만큼 감소시키기
	UFUNCTION(BlueprintCallable)
	void SubtractHour(int32 time);
	//시간을 인자대로 바꾸기 
	UFUNCTION(BlueprintCallable)
	void SetHour(int32 time);
	//시간계산 프레임 함수 (시간을 흘러가게 하기)
	UFUNCTION(BlueprintCallable)
	void CaculateTime(float deltaTime);

	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnHourChanged OnHourChanged;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 dayCount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float currentTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float timeScale = 1;

private :
	int32 prevHour = 0;
	int32 currentHour;

	//UFUNCTION(BlueprintCallable)
	//void AddTimeActor(class AC_ActorBase* _timeActor);

	//UFUNCTION(BlueprintCallable)
	//void AddTimeCharacter(class AC_EntityBase* _timeActor);

	//UFUNCTION(BlueprintCallable)
	//void OnTimeFunctionOnCharacters(int32 _TimeValue);

	//UFUNCTION(BlueprintCallable)
	//void OnTimeFunctionOnActors(int32 _TimeValue);

protected:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//TArray<class AC_ActorBase*> TimeActors;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//TArray<class AC_EntityBase*> TimeCharacters;
};



