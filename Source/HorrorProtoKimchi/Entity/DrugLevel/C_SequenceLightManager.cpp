// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/DrugLevel/C_SequenceLightManager.h"

// Sets default values
AC_SequenceLightManager::AC_SequenceLightManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_SequenceLightManager::BeginPlay()
{
	Super::BeginPlay();
	maxIndex = SequenceLightArray.Num();
}


void AC_SequenceLightManager::CalculateSequenceTime(float _DeltaTime)
{
	CurrentTime += _DeltaTime;

	if (CurrentTime > CoolTime) {
		CurrentTime -= CoolTime;

		SequenceLightArray[currentIndex]->OffLight();

		if (++currentIndex >= maxIndex) {
			currentIndex = 0;
		}

		if (SequenceLightArray[currentIndex] == nullptr) {
			currentIndex = 0;
		}
		SequenceLightArray[currentIndex]->OnLight();
	}

}

