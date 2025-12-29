// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/PuzzleLevel/C_NumberPad.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AC_NumberPad::AC_NumberPad()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("MainBody");

	DirectionComponent = CreateDefaultSubobject<UArrowComponent>("DirectionComponent");
	DirectionComponent->SetupAttachment(RootComponent);
}

void AC_NumberPad::CalculateDirection()
{

	FVector ForwardVec = DirectionComponent->GetForwardVector();

	FowardDirection = ForwardVec.GetSafeNormal();
}

FVector AC_NumberPad::CalculateCurrentPos(float _Scale)
{
	FVector ComponentLocation = DirectionComponent->GetComponentLocation();
	FVector Offset = FowardDirection * NumberArray.Num() * _Scale;
	FVector value = ComponentLocation + Offset;
	return value;
}

void AC_NumberPad::ClearNumber()
{
	for (AActor* act : NumberArray) {
		if (act && IsValid(act)) {
			act->Destroy();
		}
	}

	NumberArray.Empty();
}

