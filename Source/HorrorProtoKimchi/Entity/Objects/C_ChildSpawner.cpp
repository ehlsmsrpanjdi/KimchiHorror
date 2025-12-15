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

    // Arrow 8개 생성해서 배열에 담기
// 이유: 블프에서 각각 선택해서 위치/회전 조절 가능(컴포넌트로 존재)
    SpawnArrows.Reserve(8);

    for (int32 i = 0; i < 8; ++i)
    {
        const FName CompName = *FString::Printf(TEXT("SpawnArrow_%d"), i);

        UArrowComponent* Arrow = CreateDefaultSubobject<UArrowComponent>(CompName);
        Arrow->SetupAttachment(RootComponent);

        // 초기 배치(겹치지 않게 약간 띄워둠) - 블프에서 마음대로 수정하시면 됩니다.
        Arrow->SetRelativeLocation(FVector(i * 50.f, 0.f, 0.f));

        SpawnArrows.Add(Arrow);
    }
}

UArrowComponent* AC_ChildSpawner::GetNearestArrow(const FVector& WorldLocation) const
{
    UArrowComponent* BestArrow = nullptr;
    float BestDistSq = TNumericLimits<float>::Max();

    // 이유: sqrt 비용을 피하려고 DistSquared 사용(가장 가까운 비교만 필요)
    for (UArrowComponent* Arrow : SpawnArrows)
    {
        if (!IsValid(Arrow))
        {
            continue;
        }

        const float DistSq = FVector::DistSquared(WorldLocation, Arrow->GetComponentLocation());
        if (DistSq < BestDistSq)
        {
            BestDistSq = DistSq;
            BestArrow = Arrow;
        }
    }

    return BestArrow;
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
