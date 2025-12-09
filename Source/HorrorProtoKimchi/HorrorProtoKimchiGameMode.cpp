// Copyright Epic Games, Inc. All Rights Reserved.

#include "HorrorProtoKimchiGameMode.h"
#include "Entity/C_EntityBase.h"
#include "entity/C_ActorBase.h"

AHorrorProtoKimchiGameMode::AHorrorProtoKimchiGameMode()
{
	// stub
}

//아침 8시 기준으로 새벽 2시전까지의 시간을 반환함 0~23로 반환
int32 AHorrorProtoKimchiGameMode::GetHour()
{
	return currentTime / 3600;
}

void AHorrorProtoKimchiGameMode::AddHour(int32 time)
{
	currentTime += time*3600;

}

void AHorrorProtoKimchiGameMode::SubtractHour(int32 time)
{
	currentTime -= time * 3600;
}

void AHorrorProtoKimchiGameMode::SetHour(int32 time)
{
	currentTime = time * 60 * 60;
}

void AHorrorProtoKimchiGameMode::CaculateTime(float deltaTime)
{

	currentTime += deltaTime * timeScale;

	currentHour = currentTime / 3600;

	if (prevHour != currentHour)
	{
		if (currentHour == 24)
		{
			currentHour = 0;
			dayCount += 1;
			currentTime -= 3600 * 24;
		}

		OnHourChanged.Broadcast(currentHour);
		prevHour = currentHour;
	}

	
}





//
//void AHorrorProtoKimchiGameMode::AddTimeActor(AC_ActorBase* _timeActor)
//{
//	TimeActors.Add(_timeActor);
//}
//
//void AHorrorProtoKimchiGameMode::AddTimeCharacter(AC_EntityBase* _timeActor)
//{
//	TimeCharacters.Add(_timeActor);
//}
//
//void AHorrorProtoKimchiGameMode::OnTimeFunctionOnCharacters(int32 _TimeValue)
//{
//	for (AC_EntityBase* act : TimeCharacters) {
//		act->InvokeTimeEvent_Implementation(_TimeValue);
//	}
//}
//
//void AHorrorProtoKimchiGameMode::OnTimeFunctionOnActors(int32 _TimeValue)
//{
//	for (AC_ActorBase* act : TimeActors) {
//		act->InvokeTimeEvent_Implementation(_TimeValue);
//	}
//}
//
