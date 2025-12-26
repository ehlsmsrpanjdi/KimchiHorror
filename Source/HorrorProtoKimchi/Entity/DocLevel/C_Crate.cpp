// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/DocLevel/C_Crate.h"
#include "Debug/LogHelper.h"

// Sets default values
AC_Crate::AC_Crate()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	isPutArray.SetNum(4);
}

// Called when the game starts or when spawned
void AC_Crate::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AC_Crate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_Crate::SetBoolArray(int32 _index, bool _bool)
{
	if (_index >= isPutArray.Num()) {
		LogHelper::PrintOnly(this, "Index Override");
		return;
	}
	isPutArray[_index] = _bool;
}

int32 AC_Crate::GetFalseIndex()
{
	for (int i = 0; i < isPutArray.Num(); ++i) {
		if (isPutArray[i] == false) {
			return i;
		}
	}
	return -1;
}

int32 AC_Crate::GetTrueIndex()
{
	TArray<int> tempArray;

	for (int i = 0; i < isPutArray.Num(); ++i) {
		if (isPutArray[i] == true) {
			tempArray.Add(i);
		}
	}

	int randomIndex = FMath::RandRange(0, tempArray.Num() - 1);

	return tempArray[randomIndex];
}

TArray<AActor*> AC_Crate::SwapAmplePos()
{
	TArray<AActor*> SwappedActors;

	// 유효한 Actor가 2개 이상인지 확인
	if (AmplesArray.Num() < 2)
	{
		return SwappedActors;
	}

	// 유효한 Actor만 필터링
	TArray<AActor*> ValidActors;
	for (AActor* Actor : AmplesArray)
	{
		if (Actor && IsValid(Actor))
		{
			ValidActors.Add(Actor);
		}
	}

	if (ValidActors.Num() < 2) {
		return SwappedActors;
	}

	// 랜덤으로 2개 선택
	int32 Index1 = FMath::RandRange(0, ValidActors.Num() - 1);
	AActor* Actor1 = ValidActors[Index1];

	// 배열에서 제거
	ValidActors.RemoveAt(Index1);

	// 남은 것 중에서 랜덤 선택
	int32 Index2 = FMath::RandRange(0, ValidActors.Num() - 1);
	AActor* Actor2 = ValidActors[Index2];

	// 위치 교환
	FVector Temp = Actor1->GetActorLocation();
	Actor1->SetActorLocation(Actor2->GetActorLocation());
	Actor2->SetActorLocation(Temp);

	// 결과 배열에 추가
	SwappedActors.Add(Actor1);
	SwappedActors.Add(Actor2);

	return SwappedActors;
}


bool AC_Crate::CheckCanSwap()
{
	TArray<int> tempArray;

	for (int i = 0; i < isPutArray.Num(); ++i) {
		if (isPutArray[i] == true) {
			tempArray.Add(i);
		}
	}

	return tempArray.Num() >= 2;
}

AActor* AC_Crate::GetRandomAmple()
{
	TArray<int> tempArray;

	for (int i = 0; i < isPutArray.Num(); ++i) {
		if (isPutArray[i] == true) {
			tempArray.Add(i);
		}
	}


	if (tempArray.Num() == 0) {
		return nullptr;
	}


	int randomIndex = FMath::RandRange(0, tempArray.Num() - 1);

	return AmplesArray[tempArray[randomIndex]];
}
