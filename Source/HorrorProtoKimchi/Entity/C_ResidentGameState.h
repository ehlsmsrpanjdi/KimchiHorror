// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "C_ResidentGameState.generated.h"

/**
 *
 */
UCLASS()
class HORRORPROTOKIMCHI_API AC_ResidentGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void FindAllAngry();

	UFUNCTION(BlueprintCallable)
	void RemoveAngryNurse();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AngryNurseCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Life = 3;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void GameStart();

	UFUNCTION(BlueprintCallable)
	void LoseLife();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void LoseAllLife();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class AC_InterNurseHalusi*> Phase1Nurses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class AC_InterNurseHalusi*> Phase2Nurses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class AC_InterNurseHalusi*> Phase3Nurses;

	UFUNCTION(BlueprintCallable)
	TArray<class AC_InterNurseHalusi*> GetNowPhaseNurses();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentPhase = 0;


	UFUNCTION(BlueprintCallable)
	void AddNurseAboutPhaseNumber(class AC_InterNurseHalusi* Nurse);

	UFUNCTION(BlueprintCallable)
	void SetRandomThreeSetTrue(int32 _Phase);

	UFUNCTION(BlueprintCallable)
	void SetNextPhase(int32 _Current, int32 _Prev = -1);

	UPROPERTY()
	FTimerHandle PhaseActiveTimer;
	UPROPERTY()
	FTimerHandle PhaseSleepTimer;
	UPROPERTY()
	TArray<AC_InterNurseHalusi*> PendingActiveNurses;
	UPROPERTY()
	TArray<AC_InterNurseHalusi*> PendingSleepNurses;

	UPROPERTY()
	int32 ActiveIndex = 0;
	UPROPERTY()
	int32 SleepIndex = 0;

	UPROPERTY()
	float PhaseActivateDuration = 1.5f; // 1~2초 목표

	void ProcessActiveOne();
	void ProcessSleepOne();

	UFUNCTION()
	TArray<class AC_InterNurseHalusi*> GetPhaseArray(int32 Phase);
};
