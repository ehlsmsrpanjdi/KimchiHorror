// Fill out your copyright notice in the Description page of Project Settings.


#include "Doubt/C_DoubtsManager.h"
#include "Kismet/GameplayStatics.h"
#include "HorrorProtoKimchiCharacter.h"

UC_DoubtsManager* UC_DoubtsManager::GetDoubtsManager(const UObject* WorldContextObject)
{
	if (!WorldContextObject)
		return nullptr;

	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);
	if (!GameInstance)
		return nullptr;

	return GameInstance->GetSubsystem<UC_DoubtsManager>();
}

void UC_DoubtsManager::SetDoubt(int32 doubt)
{
	for (AC_EntityBase* var : Entitys)
	{
		if (var)
		{
			var->SetNoise(doubt);
		}
	}
	UWorld* World = GetWorld();
	if (!World) return;

	AHorrorProtoKimchiCharacter* Player =
		Cast<AHorrorProtoKimchiCharacter>(UGameplayStatics::GetPlayerCharacter(World, 0));

	if (Player)
	{
		Player->SetNoise(doubt);
	}
}
	

