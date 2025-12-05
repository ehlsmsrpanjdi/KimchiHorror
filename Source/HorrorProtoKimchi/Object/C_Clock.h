// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_Clock.generated.h"

class UArrowComponent;
class AHorrorProtoKimchiGameMode;

UCLASS()
class HORRORPROTOKIMCHI_API AC_Clock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_Clock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clock")
	UArrowComponent* HourNiddle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clock")
	UArrowComponent* MinuteNiddle;

	// BP_Stage01 레퍼런스
	UPROPERTY()
	AHorrorProtoKimchiGameMode* gameMode;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

};
