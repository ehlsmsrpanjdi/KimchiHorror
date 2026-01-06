// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/DocLevel/C_DocDoor.h"

// Sets default values
AC_DocDoor::AC_DocDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_DocDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_DocDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

