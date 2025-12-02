// Copyright Epic Games, Inc. All Rights Reserved.

#include "HorrorProtoKimchiGameMode.h"

AHorrorProtoKimchiGameMode::AHorrorProtoKimchiGameMode()
{
	// stub
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
	}
}
