// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/Stage_1/C_CrazyDoc.h"
#include "AIController.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Debug/LogHelper.h"

AC_CrazyDoc::AC_CrazyDoc()
{
	PrimaryActorTick.bCanEverTick = true;

	// BoxCollision 컴포넌트 생성
	DetectionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("DetectionBox"));
	DetectionBox->SetupAttachment(RootComponent);
	DetectionBox->SetBoxExtent(FVector(500.0f, 500.0f, 200.0f));
	DetectionBox->SetCollisionProfileName(TEXT("Trigger"));

	bIsChasing = false;
	TargetPlayer = nullptr;
}

void AC_CrazyDoc::BeginPlay()
{
	Super::BeginPlay();

	// AI Controller 생성
	AIController = Cast<AAIController>(GetController());
	if (!AIController)
	{
		AIController = GetWorld()->SpawnActor<AAIController>(AAIController::StaticClass());
		if (AIController)
		{
			AIController->Possess(this);
		}
	}


}

void AC_CrazyDoc::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsChasing && TargetPlayer)
	{
		ChasePlayer();
		return;
	}

	if (true == IsNotice) {
		currentTime += DeltaTime;

		if (currentTime > delayTime) {
			currentTime -= delayTime;
			++answerCount;
			GetRandomItem();
			CallPlayer();
		}

		if (answerCount >= 2) {
			bIsChasing = true;
			ChaseTalk();
		}
	}


}

void AC_CrazyDoc::ChasePlayer()
{
	if (!AIController || !TargetPlayer)
	{
		return;
	}

	// Navigation을 사용하여 플레이어 위치로 이동
	AIController->MoveToActor(TargetPlayer, 5.0f, true, true, true, 0, true);
}

void AC_CrazyDoc::OnPlayerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		IsNotice = true;
		currentTime = 0.f;
		answerCount = 0;
		TargetPlayer = Cast<ACharacter>(OtherActor);
	}
}

void AC_CrazyDoc::OnPlayerExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		IsNotice = false;
		TargetPlayer = nullptr;
	}
}

void AC_CrazyDoc::CallPlayer_Implementation()
{
}

void AC_CrazyDoc::ChaseTalk_Implementation()
{
}

void AC_CrazyDoc::GetRandomItem()
{
	// isFind와 Items 배열 크기 확인
	if (Items.Num() == 0 || Items.Num() != isFind.Num())
	{
		LogHelper::Log(this, TEXT("items size == 0 or items bool size is not correct"));
		return;
	}

	// 아직 찾지 않은 아이템의 인덱스만 모음
	TArray<int32> AvailableIndices;
	for (int32 i = 0; i < isFind.Num(); ++i)
	{
		if (!isFind[i] && Items[i] != nullptr)
		{
			AvailableIndices.Add(i);
		}
	}

	if (AvailableIndices.Num() == 0)
	{
		LogHelper::Log(this, TEXT("No More Chance"));
		return;
	}

	// 랜덤 인덱스 선택
	int32 RandomIndex = AvailableIndices[FMath::RandRange(0, AvailableIndices.Num() - 1)];
	selectedObj = Items[RandomIndex];
}

bool AC_CrazyDoc::ReceiveItem(AActor* Obj)
{
	if (selectedObj == Obj) {
		int32 index = Items.Find(Obj);
		isFind[index] = true;
		answerCount = 0;
		currentTime = 0;
		selectedObj = nullptr;
		return true;
	}

	else {
		bIsChasing = true;
		return false;
	}
}
