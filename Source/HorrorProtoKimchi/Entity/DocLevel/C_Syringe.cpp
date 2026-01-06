// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/DocLevel/C_Syringe.h"

// Sets default values
AC_Syringe::AC_Syringe()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_Syringe::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_Syringe::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

