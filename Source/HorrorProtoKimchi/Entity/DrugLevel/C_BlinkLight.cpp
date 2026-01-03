// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/DrugLevel/C_BlinkLight.h"

// Sets default values
AC_BlinkLight::AC_BlinkLight()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_BlinkLight::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AC_BlinkLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AC_BlinkLight::GetFlickerNoise(float MinIntensity, float MaxIntensity, float Speed) {
	float Time = GetWorld()->GetTimeSeconds();
	float Noise = FMath::PerlinNoise1D(Time * Speed);
	float Normalized = (Noise + 1.f) * 0.5f;
	return FMath::Lerp(MinIntensity, MaxIntensity, Normalized);
}

void AC_BlinkLight::OffLight_Implementation()
{
}

void AC_BlinkLight::OnLight_Implementation()
{
}
