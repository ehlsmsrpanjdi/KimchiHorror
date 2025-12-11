// Fill out your copyright notice in the Description page of Project Settings.


#include "Doubt/C_DoubtsManager.h"


void UC_DoubtsManager::SetDoubt(int32 doubt)
{
	for (AC_EntityBase* var : Entitys)
	{
		if (var)
		{
			/*var->SetNoise(doubt);*/
		}
	}
		AC_CharacterPPB* Player = Cast<AC_CharacterPPB>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (Player)
		{
			Player->SetNoise(doubt);
		}

}
