// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/Subsystem.h"
#include "Entity/C_EntityBase.h"
#include "Doubt/C_CharacterPPB.h"
#include "Kismet/GameplayStatics.h"
#include "C_DoubtsManager.generated.h"

/**
 * 
 */
UCLASS()
class HORRORPROTOKIMCHI_API UC_DoubtsManager : public USubsystem
{
	GENERATED_BODY()
public :

	UFUNCTION(BlueprintCallable)
	void SetDoubt(int32 doubt);
	
private:

	TArray<AC_EntityBase*>Entitys;
};
