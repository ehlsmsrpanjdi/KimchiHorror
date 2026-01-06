// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/DocLevel/C_Crate.h"
#include "Debug/LogHelper.h"
#include "Entity/DocLevel/C_Ample.h"
#include "Components/ArrowComponent.h"
#include "HorrorProtoKimchiCharacter.h"
#include "Entity/DocLevel/C_DocLevelComponent.h"
#include "C_KimchiHelper.h"

// Sets default values
AC_Crate::AC_Crate()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	isPutArray.SetNum(4);
}


void AC_Crate::InteractionEvent()
{
	ACharacter* Character = GetWorld()->GetFirstPlayerController()->GetCharacter();

	UC_DocLevelComponent* DocComponent = Character->GetComponentByClass<UC_DocLevelComponent>();

	if (DocComponent == nullptr) {
		LogHelper::PrintOnly(this, "지금 플레이어한테 컴포넌트 없음");
	}

	if (DocComponent->SelectedAmple == nullptr) {
		return;
	}
	else {
		DocComponent->SelectedAmple->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
		PutAmple(DocComponent->SelectedAmple);
		DocComponent->SelectedAmple = nullptr;
	}
}

void AC_Crate::PutAmple(AC_Ample* Ample)
{
	if (Ample == nullptr) {
		LogHelper::PrintOnly(this, "앰플이 없는데 앰플을 어케 놨음");
		return;
	}

	if (ArrowsArray.Num() == 0) {
		LogHelper::PrintOnly(this, "에로우 컴포넌트 배열 비어있음");
		return;
	}

	for (int i = 0; i < isPutArray.Num(); ++i) {
		if (isPutArray[i] == false) {
			isPutArray[i] = true;
			AmplesArray.Add(Ample);
			Ample->SetActorLocation(ArrowsArray[i]->GetComponentLocation());
			Ample->CurrentCrate = this;
			Ample->CurrentCrateIndex = i;
			break;
		}
	}
}

void AC_Crate::PutOffAmple(AC_Ample* Ample)
{
	if (Ample == nullptr) {
		LogHelper::PrintOnly(this, "앰플이 없는데 앰플을 어케 가져감");
		return;
	}

	int32 currentIndex = Ample->CurrentCrateIndex;

	isPutArray[currentIndex] = false;

	AmplesArray.Remove(Ample);
}

void AC_Crate::EHIHIEvent()
{
	if (bIsAlreadyPut == true) {
		return;
	}

	if (AmplesArray.Num() < 0) {
		return;
	}

	if (AmplesArray.Num() == 1) {
		ReturnEHIHI();
	}
	else {
		int32 val = UC_KimchiHelper::GetRandomInteger(0, 1);
		if (val == 0) {
			ReturnEHIHI();
		}
		else {
			SwapEHIHI();
		}
	}


}

void AC_Crate::SwapEHIHI()
{
	TArray<int32> tempArray;

	if (AmplesArray.Num() < 2) {
		return;
	}

	for (int i = 0; i < AmplesArray.Num(); ++i) {
		if (AmplesArray[i]->bIsInteracting == false) {
			tempArray.Add(i);
		}
	}

	if (tempArray.Num() < 2) {
		return;
	}

	int32 randomInt_1 = UC_KimchiHelper::GetRandomInteger(0, tempArray.Num() - 1);
	int32 firstIndex = tempArray[randomInt_1];
	tempArray.RemoveAt(randomInt_1);

	int32 randomInt_2 = UC_KimchiHelper::GetRandomInteger(0, tempArray.Num() - 1);

	int32 secondIndex = tempArray[randomInt_2];


	AC_Ample* First = AmplesArray[firstIndex];
	AC_Ample* Second = AmplesArray[secondIndex];


	int32 tempIndex = 0;

	tempIndex = First->CurrentCrateIndex;
	First->CurrentCrateIndex = Second->CurrentCrateIndex;
	First->SetActorLocation(ArrowsArray[First->CurrentCrateIndex]->GetComponentLocation());

	Second->CurrentCrateIndex = tempIndex;
	Second->SetActorLocation(ArrowsArray[Second->CurrentCrateIndex]->GetComponentLocation());
}

void AC_Crate::ReturnEHIHI()
{
	if (AmplesArray.Num() <= 0) {
		return;
	}

	TArray<int32> tempArray;

	for (int i = 0; i < AmplesArray.Num(); ++i) {
		if (AmplesArray[i]->bIsInteracting == false) {
			tempArray.Add(i);
		}
	}

	if (tempArray.Num() <= 0) {
		return;
	}

	int32 randomInt = UC_KimchiHelper::GetRandomInteger(0, tempArray.Num() - 1);

	int32 RandomIndex = tempArray[randomInt];

	AC_Ample* SelectedAmple = AmplesArray[RandomIndex];
	PutOffAmple(SelectedAmple);
	OtherCrate->PutAmple(SelectedAmple);
}

bool AC_Crate::CalCulateEHIHI(float _DeltaTime)
{
	if (bIsEHIHI == false) {
		return false;
	}

	if (isEnd == true) {
		return false;
	}

	CurrentTime += _DeltaTime;

	if (CurrentTime > CoolTime) {
		CurrentTime -= CoolTime;
		return true;
	}
	return false;
}

//TArray<AActor*> AC_Crate::SwapAmplePos()
//{
//	TArray<AActor*> SwappedActors;
//
//	// 유효한 Actor가 2개 이상인지 확인
//	if (AmplesArray.Num() < 2)
//	{
//		return SwappedActors;
//	}
//
//	// 유효한 Actor만 필터링
//	TArray<AActor*> ValidActors;
//	for (AActor* Actor : AmplesArray)
//	{
//		if (Actor && IsValid(Actor))
//		{
//			ValidActors.Add(Actor);
//		}
//	}
//
//	if (ValidActors.Num() < 2) {
//		return SwappedActors;
//	}
//
//	// 랜덤으로 2개 선택
//	int32 Index1 = FMath::RandRange(0, ValidActors.Num() - 1);
//	AActor* Actor1 = ValidActors[Index1];
//
//	// 배열에서 제거
//	ValidActors.RemoveAt(Index1);
//
//	// 남은 것 중에서 랜덤 선택
//	int32 Index2 = FMath::RandRange(0, ValidActors.Num() - 1);
//	AActor* Actor2 = ValidActors[Index2];
//
//	// 위치 교환
//	FVector Temp = Actor1->GetActorLocation();
//	Actor1->SetActorLocation(Actor2->GetActorLocation());
//	Actor2->SetActorLocation(Temp);
//
//	// 결과 배열에 추가
//	SwappedActors.Add(Actor1);
//	SwappedActors.Add(Actor2);
//
//	return SwappedActors;
//}
//
//
//bool AC_Crate::CheckCanSwap()
//{
//	TArray<int> tempArray;
//
//	for (int i = 0; i < isPutArray.Num(); ++i) {
//		if (isPutArray[i] == true) {
//			tempArray.Add(i);
//		}
//	}
//
//	return tempArray.Num() >= 2;
//}
//
//AActor* AC_Crate::GetRandomAmple()
//{
//	TArray<int> tempArray;
//
//	for (int i = 0; i < isPutArray.Num(); ++i) {
//		if (isPutArray[i] == true) {
//			tempArray.Add(i);
//		}
//	}
//
//
//	if (tempArray.Num() == 0) {
//		return nullptr;
//	}
//
//
//	int randomIndex = FMath::RandRange(0, tempArray.Num() - 1);
//
//	return AmplesArray[tempArray[randomIndex]];
//}


