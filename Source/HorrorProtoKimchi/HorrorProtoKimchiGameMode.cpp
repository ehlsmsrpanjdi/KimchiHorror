// Copyright Epic Games, Inc. All Rights Reserved.

#include "HorrorProtoKimchiGameMode.h"

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
	currentDelayTime += GetWorld()->DeltaTimeSeconds;

	while(currentTime >= _Delaytime){
		currentDelayTime -= _Delaytime;

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
