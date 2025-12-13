// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity/C_ActorBase.h"
#include "Components/AudioComponent.h"   // AudioComponent 헤더
#include "Sound/SoundBase.h"             // Sound asset 헤더
#include "Components/ArrowComponent.h"
#include "C_ChildSpawner.generated.h"

/**
 * 
 */
UCLASS()
class HORRORPROTOKIMCHI_API AC_ChildSpawner : public AC_ActorBase
{
	GENERATED_BODY()

public:
	AC_ChildSpawner();


public:

	virtual void SetActiveFalse() override;

	virtual void SetActiveTrue() override;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sound")
	UAudioComponent* AudioComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound")
	USoundBase* SoundCue;

	// 블루프린트에서 위치를 옮길 "스폰 포인트(Arrow)"들
// 이유: 블프에서 컴포넌트 이동이 편하고, 배열로 탐색하기 쉬움
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpawnPoints")
	TArray<TObjectPtr<UArrowComponent>> SpawnArrows;

	// 입력 위치에서 가장 가까운 Arrow 반환
// 이유: 스폰 로직에서 가장 근접한 포인트를 빠르게 선택 가능
	UFUNCTION(BlueprintCallable, Category = "SpawnPoints")
	UArrowComponent* GetNearestArrow(const FVector& WorldLocation) const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsActive = false;
};
