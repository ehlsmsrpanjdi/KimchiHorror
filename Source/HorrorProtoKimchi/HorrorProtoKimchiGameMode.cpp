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
	if (currentTime >= 5760) {  //새벽 11시
		return currentTime / 360 - 16;
	}
	else {
		return currentTime / 360 + 8;
	}
}

void AHorrorProtoKimchiGameMode::CalculateTime(float _Delaytime)
{
	currentDelayTime += _Delaytime;

	while (currentTime <= currentDelayTime) {
		currentDelayTime -= currentTime;

		//한바뀌 다 돌았으면
		if (minute >= 360) {
			++currentTime;
			minute = 1;
		}
		else {
			minute += 1;
			++currentTime;
		}

		if (minute % 12 == 0) {
			hour += 1;

			if (hour % 30 == 0) {
				SetHour();
			}
		}

		if (hour >= 360) {
			hour = 0;
		}

		if (currentTime >= 6480) {
			currentTime = 0;
			++DayCount;
		}
	}
}

void AHorrorProtoKimchiGameMode::SetHour()
{
	currentHour = GetHour();

	OnHourChanged.Broadcast(currentHour);

	//OnTimeFunctionOnCharacters(currentHour);
	//OnTimeFunctionOnActors(currentHour);
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
