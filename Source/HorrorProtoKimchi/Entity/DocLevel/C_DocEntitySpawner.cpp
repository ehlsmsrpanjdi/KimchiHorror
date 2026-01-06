// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/DocLevel/C_DocEntitySpawner.h"
#include "GameFramework/Character.h"
#include "Components/ArrowComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
AC_DocEntitySpawner::AC_DocEntitySpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Rootcomponent"));

	Point_1 = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnPoint_1"));
	Point_1->SetupAttachment(RootComponent);
	SpawnPointArray.Add(Point_1);

	Point_2 = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnPoint_2"));
	Point_2->SetupAttachment(RootComponent);
	SpawnPointArray.Add(Point_2);

	Point_3 = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnPoint_3"));
	Point_3->SetupAttachment(RootComponent);
	SpawnPointArray.Add(Point_3);

	Point_4 = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnPoint_4"));
	Point_4->SetupAttachment(RootComponent);
	SpawnPointArray.Add(Point_4);

	Point_5 = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnPoint_5"));
	Point_5->SetupAttachment(RootComponent);
	SpawnPointArray.Add(Point_5);

	Point_6 = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnPoint_6"));
	Point_6->SetupAttachment(RootComponent);
	SpawnPointArray.Add(Point_6);

	IsSpawnArray.SetNum(SpawnPointArray.Num());
}

bool AC_DocEntitySpawner::CalculateTime(float _DeltaTime) {
	if (isEnd == true) {
		return false;
	}

	if (EntityArray.Num() != 3) {
		PhaseCurrentTime += _DeltaTime;

		if (PhaseCurrentTime > PhaseCoolTime) {
			PhaseCurrentTime -= PhaseCoolTime;
			if (EntityArray.Num() == 1) {
				EntityArray.Add(Phase_2Entity);
			}
			else if (EntityArray.Num() == 2) {
				EntityArray.Add(Phase_3Entity);
			}
		}
	}

	currentTime += _DeltaTime;
	if (currentTime > CoolTime) {
		currentTime -= CoolTime;
		return true;
	}
	return false;
}

TSubclassOf<ACharacter> AC_DocEntitySpawner::GetRandomCharacter()
{
	if (EntityArray.Num() == 0) {
		return nullptr;
	}

	int32 randomIndex = FMath::RandRange(0, EntityArray.Num() - 1);

	return EntityArray[randomIndex];
}

UArrowComponent* AC_DocEntitySpawner::GetRandomPoint()
{
	if (SpawnPointArray.Num() == 0) {
		return nullptr;
	}

	// 사용 가능한 스폰 포인트 찾기
	TArray<int32> AvailableIndices;
	for (int32 i = 0; i < SpawnPointArray.Num(); ++i)
	{
		if (!IsSpawnArray[i]) // false인 것만
		{
			AvailableIndices.Add(i);
		}
	}

	// 사용 가능한 포인트가 없으면 nullptr 반환
	if (AvailableIndices.Num() == 0)
	{
		return nullptr;
	}

	// 사용 가능한 포인트 중 랜덤 선택
	int32 RandomAvailableIndex = AvailableIndices[FMath::RandRange(0, AvailableIndices.Num() - 1)];
	IsSpawnArray[RandomAvailableIndex] = true;

	currentSelectedIndex = RandomAvailableIndex;

	return SpawnPointArray[RandomAvailableIndex];
}

void AC_DocEntitySpawner::SetupPointPos(float SpawnDistance)
{
	// Point_1: 10시 30분 위치 (315도)
	Point_1->SetRelativeLocation(FVector(
		SpawnDistance * FMath::Cos(FMath::DegreesToRadians(315.0f)),
		SpawnDistance * FMath::Sin(FMath::DegreesToRadians(315.0f)),
		0.0f
	));
	Point_1->SetRelativeRotation(FRotator(0.0f, 135.0f, 0.0f));

	// Point_2: 9시 위치 (270도)
	Point_2->SetRelativeLocation(FVector(
		SpawnDistance * FMath::Cos(FMath::DegreesToRadians(270.0f)),
		SpawnDistance * FMath::Sin(FMath::DegreesToRadians(270.0f)),
		0.0f
	));
	Point_2->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));

	// Point_3: 7시 30분 위치 (225도)
	Point_3->SetRelativeLocation(FVector(
		SpawnDistance * FMath::Cos(FMath::DegreesToRadians(225.0f)),
		SpawnDistance * FMath::Sin(FMath::DegreesToRadians(225.0f)),
		0.0f
	));
	Point_3->SetRelativeRotation(FRotator(0.0f, 45.0f, 0.0f));

	// Point_4: 1시 30분 위치 (45도)
	Point_4->SetRelativeLocation(FVector(
		SpawnDistance * FMath::Cos(FMath::DegreesToRadians(45.0f)),
		SpawnDistance * FMath::Sin(FMath::DegreesToRadians(45.0f)),
		0.0f
	));
	Point_4->SetRelativeRotation(FRotator(0.0f, 225.0f, 0.0f));

	// Point_5: 3시 위치 (90도)
	Point_5->SetRelativeLocation(FVector(
		SpawnDistance * FMath::Cos(FMath::DegreesToRadians(90.0f)),
		SpawnDistance * FMath::Sin(FMath::DegreesToRadians(90.0f)),
		0.0f
	));
	Point_5->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));

	// Point_6: 4시 30분 위치 (135도)
	Point_6->SetRelativeLocation(FVector(
		SpawnDistance * FMath::Cos(FMath::DegreesToRadians(135.0f)),
		SpawnDistance * FMath::Sin(FMath::DegreesToRadians(135.0f)),
		0.0f
	));
	Point_6->SetRelativeRotation(FRotator(0.0f, 315.0f, 0.0f));
}

void AC_DocEntitySpawner::ResetSpawnPointBool(int _index)
{
	IsSpawnArray[_index] = false;
}

AActor* AC_DocEntitySpawner::SpawnEntity()
{
	UArrowComponent* Point = GetRandomPoint();


	TSubclassOf<ACharacter> EntityClass = GetRandomCharacter();

	AActor* SpawnedEntity = GetWorld()->SpawnActor(EntityClass, &Point->GetComponentTransform());

	return SpawnedEntity;
}

