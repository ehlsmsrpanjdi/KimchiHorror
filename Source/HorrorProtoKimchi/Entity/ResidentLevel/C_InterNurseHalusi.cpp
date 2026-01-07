// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/ResidentLevel/C_InterNurseHalusi.h"
#include "Entity/C_ResidentGameState.h"
#include "Sequence/C_SequenceHelper.h"
#include "C_GameInstance.h"
#include "Doubt/C_DoubtsManager.h"
#include "GameFramework/CharacterMovementComponent.h"


AC_InterNurseHalusi::AC_InterNurseHalusi()
{
	Medicine = CreateDefaultSubobject<UStaticMeshComponent>("Medicine");
	Medicine->SetupAttachment(RootComponent);
}

void AC_InterNurseHalusi::InteractionEvent() {
	if (bisInteracted == true) {
		return;
	}

	if (bIsTrueNS == true) {
		if (bIsEnd == true) {
			UC_GameInstance* Instance = Cast<UC_GameInstance>(GetGameInstance());
			++Instance->DayCount;
			SequenceHelper->RunSequence();
		}
		else {
			Medicine->DestroyComponent();
			bisInteracted = true;
			AC_ResidentGameState* GameState = Cast<AC_ResidentGameState>(GetWorld()->GetGameState());
			GameState->RemoveAngryNurse();
			CorrectNurse();
		}
	}

	else {
		Medicine->DestroyComponent();
		AC_ResidentGameState* GameState = Cast<AC_ResidentGameState>(GetWorld()->GetGameState());
		GameState->LoseLife();
		WrongNurse();
		bisInteracted = true;
	}
}

bool AC_InterNurseHalusi::CalculateShaking(float _DeltaTime)
{
	if (bisInteracted == true) {
		return false;
	}

	CurrentTime -= _DeltaTime;

	if (CurrentTime < 0) {
		CurrentTime = CoolTime;
		return true;
	}

	return false;
}

void AC_InterNurseHalusi::CalculateFace(float _DeltaTime)
{
	if (FaceCurrentTime > FaceCoolTime) {
		return;
	}
	else {
		FaceCurrentTime += _DeltaTime;
		if (FaceCurrentTime > FaceCoolTime) {
			FaceFunction();
		}
	}
}

void AC_InterNurseHalusi::ActiveMode()
{
	OffAll(false);
}

void AC_InterNurseHalusi::SleepMode()
{
	OffAll(true);
}

void AC_InterNurseHalusi::OffAll(bool bDormant)
{
	// 1. Actor Tick
	SetActorTickEnabled(!bDormant);

	// 2. 전체 Actor 가시성
	SetActorHiddenInGame(bDormant);

	// 3. 충돌 (필요 없으면 끔)
	SetActorEnableCollision(!bDormant);

	for (USkeletalMeshComponent* SkelMesh : DormantIncludeMeshes) {

		// 컴포넌트 Tick
		SkelMesh->SetComponentTickEnabled(!bDormant);

	}
}
