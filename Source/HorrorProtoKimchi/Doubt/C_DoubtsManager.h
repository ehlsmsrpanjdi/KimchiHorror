// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/Subsystem.h"
#include "Entity/C_EntityBase.h"
#include "Doubt/C_CharacterPPB.h"
#include "Subsystems/GameInstanceSubsystem.h" 
#include "C_DoubtsManager.generated.h"

/**
 * 
 */
UCLASS()
class HORRORPROTOKIMCHI_API UC_DoubtsManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public :
	static UC_DoubtsManager* GetDoubtsManager(const UObject* WorldContextObject);
	UFUNCTION(BlueprintCallable)
	void SetDoubt(int32 doubt);
	
	TArray<AC_EntityBase*>Entitys;
};
