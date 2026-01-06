// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/DocLevel/C_Ample.h"
#include "Entity/DocLevel/C_Crate.h"
#include "C_DocLevelComponent.h"
#include "Debug/LogHelper.h"
#include "HorrorProtoKimchiCharacter.h"

// Sets default values
AC_Ample::AC_Ample()
{

}

bool AC_Ample::InteractionDrug()
{
	ACharacter* Character = GetWorld()->GetFirstPlayerController()->GetCharacter();

	UC_DocLevelComponent* DocComponent = Character->GetComponentByClass<UC_DocLevelComponent>();

	//주사기 들고있는데 약물이 없다면
	if (DocComponent->SelectedSyringe != nullptr) {
		if (false == DocComponent->bOnAmple) {
			AddDrug();
			return true;
		}
	}

	//주사기 안들고있는데 엠플도 안들고있다면
	if (DocComponent->SelectedAmple == nullptr) {
		GainDrug();
	}
	return false;
}

void AC_Ample::AddDrug()
{
	ACharacter* Character = GetWorld()->GetFirstPlayerController()->GetCharacter();

	UC_DocLevelComponent* DocComponent = Character->GetComponentByClass<UC_DocLevelComponent>();

	if (DocComponent == nullptr) {
		LogHelper::PrintOnly(GetWorld(), "플레이어한테 컴포넌트없음");
		return;
	}

	DocComponent->AddDrug(this);

	bIsInteracting = true;
}

void AC_Ample::GainDrug()
{
	ACharacter* Character = GetWorld()->GetFirstPlayerController()->GetCharacter();

	UC_DocLevelComponent* DocComponent = Character->GetComponentByClass<UC_DocLevelComponent>();

	if (DocComponent == nullptr) {
		LogHelper::PrintOnly(GetWorld(), "플레이어한테 컴포넌트없음");
		return;
	}

	if (CurrentCrate != nullptr) {
		CurrentCrate->PutOffAmple(this);
	}

	DocComponent->GainAmple(this);
}


void AC_Ample::EndInteraction() {
	bIsInteracting = false;
}