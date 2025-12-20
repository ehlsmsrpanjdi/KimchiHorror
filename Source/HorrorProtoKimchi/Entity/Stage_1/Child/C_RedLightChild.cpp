// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/Stage_1/Child/C_RedLightChild.h"
#include "Components/ArrowComponent.h"
#include "HorrorProtoKimchiCharacter.h"
#include "Debug/LogHelper.h"
#include "HorrorProtoKimchiPlayerController.h"


AC_RedLightChild::AC_RedLightChild()
{
	ForwardDirection = CreateDefaultSubobject<UArrowComponent>("ForwardDirection");
	ForwardDirection->SetupAttachment(RootComponent);

	BackDirection = CreateDefaultSubobject<UArrowComponent>("BackDirection");
	BackDirection->SetupAttachment(RootComponent);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>("AudioComponent");
}



void AC_RedLightChild::OnSoundFinished()
{
	IsChecking = true;
	if (Player == nullptr) {
		return;
	}
	Player->PlayerYaw = 0;
	Player->PlayerPitch = 0;
	SetDirectionToBack();

	GetWorldTimerManager().SetTimer(SoundFinishedTimer, this, &AC_RedLightChild::PlayRedLight, 4.f, false);
}

void AC_RedLightChild::PlayRedLight()
{
	if (!RedLightSound) {
		return;
	}

	if (!AudioComponent) {
		return;
	}

	SetDirectionToForward();
	AudioComponent->SetSound(RedLightSound);
	AudioComponent->OnAudioFinished.AddDynamic(this, &AC_RedLightChild::OnSoundFinished);
	AudioComponent->Play();
}

void AC_RedLightChild::StopRedLightGame()
{
	IsChecking = false;
	GetWorldTimerManager().ClearTimer(SoundFinishedTimer);

	if (AudioComponent) {
		AudioComponent->Stop();
		AudioComponent->OnAudioFinished.Clear();
	}
}

void AC_RedLightChild::SetDirectionToForward()
{
	LookDirection = ForwardDirection->GetComponentLocation();
}

void AC_RedLightChild::SetDirectionToBack()
{
	LookDirection = BackDirection->GetComponentLocation();
}

bool AC_RedLightChild::CheckPlayerMove()
{
	if (IsChecking == false) {
		return true;
	}

	FVector playerVelocity = Player->GetVelocity();
	float speed = playerVelocity.Length();
	if (10 < speed) {
		return false;
	}

	if (FMath::Abs(Player->PlayerYaw) > 0.05) {
		return false;
	}
	if (FMath::Abs(Player->PlayerPitch) > 0.05) {
		return false;
	}
	return true;
}
