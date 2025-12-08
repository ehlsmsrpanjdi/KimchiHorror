// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/Objects/C_ChildSpawner.h"

AC_ChildSpawner::AC_ChildSpawner()
{
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    SetRootComponent(RootComponent);

    AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
    AudioComp->SetupAttachment(RootComponent);
    AudioComp->bAutoActivate = false;
    bIsActive = false;
}

void AC_ChildSpawner::SetActiveFalse()
{
	Super::SetActiveFalse();
    if (AudioComp)
    {
        // 콜백 바인딩 제거 (엔티티 스폰 방지)
        AudioComp->OnAudioFinished.RemoveAll(this);

        // 재생 중이었으면 강제로 중단
        if (AudioComp->IsPlaying())
        {
            AudioComp->Stop();
        }
    }
}

void AC_ChildSpawner::SetActiveTrue()
{
    Super::SetActiveTrue();
}
