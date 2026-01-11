// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/C_ResidentGameState.h"
#include "Doubt/C_DoubtsManager.h"
#include "Entity/ResidentLevel/C_InterNurseHalusi.h"

void AC_ResidentGameState::RemoveAngryNurse()
{
	--AngryNurseCount;
	if (AngryNurseCount <= 0) {
		FindAllAngry();
	}
}


void AC_ResidentGameState::LoseLife()
{
	--Life;
	UC_DoubtsManager::GetDoubtsManager(GetWorld())->SetDoubt(10);
	TArray<AC_InterNurseHalusi*> RefArray = GetNowPhaseNurses();

	for (AC_InterNurseHalusi* nurse : RefArray) {
		nurse->Sneer();
	}

	if (Life <= 0) {
		LoseAllLife();
	}
}

TArray<AC_InterNurseHalusi*> AC_ResidentGameState::GetNowPhaseNurses()
{
	switch (CurrentPhase)
	{
	case 1:
		return Phase1Nurses;
	case 2:
		return Phase2Nurses;
	case 3:
		return Phase3Nurses;
	default:
		break;
	}
	TArray<AC_InterNurseHalusi*> temp = TArray<AC_InterNurseHalusi*>();
	return temp;
}

void AC_ResidentGameState::AddNurseAboutPhaseNumber(AC_InterNurseHalusi* Nurse)
{
	switch (Nurse->CurrentPhase)
	{
	case 1:
		Phase1Nurses.Add(Nurse);
		break;
	case 2:
		Phase2Nurses.Add(Nurse);
		break;
	case 3:
		Phase3Nurses.Add(Nurse);
		break;
	default:
		break;
	}
}

void AC_ResidentGameState::SetRandomThreeSetTrue(int32 Phase)
{
	TArray<AC_InterNurseHalusi*> SourceArray;

	switch (Phase)
	{
	case 1: SourceArray = Phase1Nurses; break;
	case 2: SourceArray = Phase2Nurses; break;
	case 3: SourceArray = Phase3Nurses; break;
	default:
		return;
	}

	// 안전장치
	if (SourceArray.Num() <= 3)
	{
		SourceArray[0]->bIsTrueNS = true;
		return;
	}

	// 셔플
	for (int32 i = SourceArray.Num() - 1; i > 0; --i)
	{
		int32 SwapIndex = FMath::RandRange(0, i);
		SourceArray.Swap(i, SwapIndex);
	}

	// 앞에서 3개만 추출
	TArray<AC_InterNurseHalusi*> Result;

	for (int32 i = 0; i < 3; ++i)
	{
		SourceArray[i]->bIsTrueNS = true;
	}
}

void AC_ResidentGameState::SetNextPhase(int32 _Current, int32 _Prev)
{
	// 이전 Phase Sleep
	PendingSleepNurses = GetPhaseArray(_Prev);
	SleepIndex = 0;

	if (PendingSleepNurses.Num() > 0)
	{
		const float SleepInterval =
			PhaseActivateDuration / PendingSleepNurses.Num();

		GetWorldTimerManager().SetTimer(
			PhaseSleepTimer,
			this,
			&AC_ResidentGameState::ProcessSleepOne,
			FMath::Max(0.05f, SleepInterval),
			true
		);
	}

	// 현재 Phase Active
	PendingActiveNurses = GetPhaseArray(_Current);
	ActiveIndex = 0;

	if (PendingActiveNurses.Num() > 0)
	{
		const float ActiveInterval =
			PhaseActivateDuration / PendingActiveNurses.Num();

		GetWorldTimerManager().SetTimer(
			PhaseActiveTimer,
			this,
			&AC_ResidentGameState::ProcessActiveOne,
			FMath::Max(0.05f, ActiveInterval),
			true
		);
	}
}

void AC_ResidentGameState::ProcessActiveOne()
{
	if (ActiveIndex >= PendingActiveNurses.Num())
	{
		GetWorldTimerManager().ClearTimer(PhaseActiveTimer);
		return;
	}

	if (PendingActiveNurses[ActiveIndex])
	{
		PendingActiveNurses[ActiveIndex]->ActiveMode();
	}

	ActiveIndex++;
}

void AC_ResidentGameState::ProcessSleepOne()
{
	if (SleepIndex >= PendingSleepNurses.Num())
	{
		GetWorldTimerManager().ClearTimer(PhaseSleepTimer);
		return;
	}

	if (PendingSleepNurses[SleepIndex])
	{
		PendingSleepNurses[SleepIndex]->SleepMode();
	}

	SleepIndex++;
}

TArray<AC_InterNurseHalusi*> AC_ResidentGameState::GetPhaseArray(int32 Phase)
{
	switch (Phase)
	{
	case 1: return Phase1Nurses;
	case 2: return Phase2Nurses;
	case 3: return Phase3Nurses;
	default: return {};
	}
}