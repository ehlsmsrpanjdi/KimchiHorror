// Copyright Epic Games, Inc. All Rights Reserved.

#include "HorrorPrototypeGameMode.h"
#include "HorrorPrototypeCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHorrorPrototypeGameMode::AHorrorPrototypeGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
