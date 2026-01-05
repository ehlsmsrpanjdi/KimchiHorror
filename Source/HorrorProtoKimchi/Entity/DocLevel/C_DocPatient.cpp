// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/DocLevel/C_DocPatient.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"

AC_DocPatient::AC_DocPatient()
{
	SoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SoundComponent"));
	SoundComponent->SetupAttachment(RootComponent);

	HeartBeatComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("HeartBeatComponent"));
	HeartBeatComponent->SetupAttachment(RootComponent);

}

void AC_DocPatient::ActiveAllEvent()
{
	OnAction.Broadcast();
}

bool AC_DocPatient::OnEvent(float _DeltaTime)
{
	if (HaveToCure == true) {  // 이미 아프면 걍 넘어가기
		return false;
	}

	CurrentTime += _DeltaTime;

	if (CurrentTime > CoolTime) {
		CurrentTime -= CoolTime;

		CurrentEventIndex = FMath::RandRange(0, 3);
		HaveToCure = true;
		return true;
	}
	return false;
}

bool AC_DocPatient::OnCurePatient(int32 _AmpleIndex)
{
	if (HaveToCure == false) {  //치료 할 필요 없는데 치료하면 안됨
		return false;
	}

	if (_AmpleIndex != CurrentEventIndex) {  // 약품 번호 다르면 안됨
		return false;
	}

	HaveToCure = false;
	CurrentEventIndex = -1;

	CurrentTime = 0;

	return true;
}
