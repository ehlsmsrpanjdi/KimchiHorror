// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/Stage_1/C_BlinkEntity.h"
#include "Components/SplineComponent.h"
#include "Components/BoxComponent.h"
#include "Entity/C_StateEnum.h"
#include "Entity/Stage_1/BlinkEntity/C_BlinkStatePatrol.h"
#include "Entity/Stage_1/BlinkEntity/C_BlinkStateChase.h"
#include "Entity/Stage_1/BlinkEntity/C_BlinkStateReturn.h"
#include "Entity/C_StateMachine.h"
#include "AIController.h"

AC_BlinkEntity::AC_BlinkEntity()
{
	// DetectBox 생성
	DetectBox = CreateDefaultSubobject<UBoxComponent>(TEXT("DetectBox"));
	DetectBox->SetupAttachment(RootComponent);
	DetectBox->SetBoxExtent(FVector(200, 200, 100));

	// LoseBox 생성
	LoseBox = CreateDefaultSubobject<UBoxComponent>(TEXT("LoseBox"));
	LoseBox->SetupAttachment(RootComponent);
	LoseBox->SetBoxExtent(FVector(500, 500, 200));

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

}

void AC_BlinkEntity::BeginPlay()
{
	Super::BeginPlay();

	// Overlap 이벤트 바인딩
	if (DetectBox) {
		DetectBox->OnComponentBeginOverlap.AddDynamic(
			this,
			&AC_BlinkEntity::OnPlayerDetect
		);
	}

	if (LoseBox) {
		LoseBox->OnComponentEndOverlap.AddDynamic(
			this,
			&AC_BlinkEntity::OnPlayerLose
		);
	}

	if (SplineActor)
	{
		Spline = SplineActor->FindComponentByClass<USplineComponent>();
	}

	ChangeState(C_StateEnum::Idle);
}

void AC_BlinkEntity::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AC_BlinkEntity::StateInit()
{
	// Patrol State 생성
	UC_BlinkStatePatrol* PatrolState = NewObject<UC_BlinkStatePatrol>(this);

	UC_BlinkStateChase* ChaseState = NewObject<UC_BlinkStateChase>(this);

	UC_BlinkStateReturn* ReturnState = NewObject<UC_BlinkStateReturn>(this);

	AddState(C_StateEnum::Idle, PatrolState);
	AddState(C_StateEnum::Chase, ChaseState);
	AddState(C_StateEnum::Return, ReturnState);
}

void AC_BlinkEntity::OnPlayerDetect(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	// 플레이어 감지 로직
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		TargetActor = OtherActor;
		ChangeState(C_StateEnum::Chase);
	}
}

void AC_BlinkEntity::OnPlayerLose(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (TargetActor == nullptr) {
		return;
	}
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		TargetActor = nullptr;
		ChangeState(C_StateEnum::Return);
	}
}