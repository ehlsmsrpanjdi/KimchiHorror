// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/Stage_1/C_PatientNurse.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "Debug/LogHelper.h"
#include "GameFramework/Character.h"

AC_PatientNurse::AC_PatientNurse()
{
}

void AC_PatientNurse::BeginPlay()
{
	Super::BeginPlay();
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

void AC_PatientNurse::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AC_PatientNurse::Chase(ACharacter* _target, float _Radius, float _Distance, float _waitTime)
{
	if (_target && IsValid(_target)) {
		AIController->MoveToActor(_target, 5.0f, true, true, true, 0, true);
	}

	if (_Distance > CalculateDistance(_target)) {
		++sequenceIndex;
		SetWaitTime(_waitTime);
	}
}

float AC_PatientNurse::CalculateDistance(ACharacter* _Target)
{
	if (false == IsValid(_Target)) {
		return 0.f;
	}
	FVector MyLocation = GetActorLocation();
	FVector TargetLocation = _Target->GetActorLocation();

	return FVector::Distance(MyLocation, TargetLocation);
}

void AC_PatientNurse::SetWaitTime(float _WaitTime)
{
	currentTime = 0.f;
	waitTime = _WaitTime;
}

bool AC_PatientNurse::WaitFunction(float _DeltaTime)
{
	if (currentTime < waitTime) {
		currentTime += _DeltaTime;
		return false;
	}
	else {
		return true;
	}

}
