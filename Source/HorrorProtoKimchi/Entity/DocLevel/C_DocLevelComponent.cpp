// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/DocLevel/C_DocLevelComponent.h"
#include "HorrorProtoKimchiCharacter.h"
#include "Debug/LogHelper.h"

// Sets default values for this component's properties
UC_DocLevelComponent::UC_DocLevelComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UC_DocLevelComponent::GainSyringe()
{
	//손에 뭐 들고있음 return
	if (SelectedSyringe != nullptr || SelectedAmple != nullptr) {
		return;
	}

	AHorrorProtoKimchiCharacter* Player = Cast<AHorrorProtoKimchiCharacter>(GetOwner());

	if (Player == nullptr) {
		LogHelper::PrintOnly(GetWorld(), "플레이어 캐스팅 안됨 오류");
		return;
	}

	UArrowComponent* handPosComponent = Player->HandposComponent;

	FTransform TempTransform;
	// Location
	TempTransform.SetLocation(FVector::ZeroVector);

	// Rotation (Pitch, Yaw, Roll)
	TempTransform.SetRotation(FQuat(FRotator(-90.f, 0.f, 0.f)));

	// Scale
	TempTransform.SetScale3D(FVector(1.f, 1.f, 1.f));
	AActor* SpawnedActor = GetWorld()->SpawnActor(SyringeClass, &TempTransform);
	SelectedSyringe = Cast<AC_Syringe>(SpawnedActor);

	if (SelectedSyringe == nullptr) {
		LogHelper::PrintOnly(GetWorld(), "주사기로 캐스팅 안됨 오류");
		return;
	}

	SelectedSyringe->AttachToComponent(handPosComponent, FAttachmentTransformRules::KeepRelativeTransform);
	SelectedSyringe->SetActorLocation(handPosComponent->GetComponentLocation());
}

void UC_DocLevelComponent::AddDrug(AC_Ample* Ample)
{
	//손에 뭐 들고있음 return
	if (SelectedSyringe == nullptr || SelectedAmple != nullptr) {
		return;
	}

	if (Ample != nullptr && true == IsValid(Ample)) {
		SelectedDrugIndex = Ample->DrugIndex;
		bOnAmple = true;
		//약 들고있는 상태이고 어떤 약을 들고있는지 index로 체크
	}
}

void UC_DocLevelComponent::GainAmple(AC_Ample* Ample)
{
	//손에 뭐 들고있음 return
	if (SelectedSyringe != nullptr || SelectedAmple != nullptr) {
		return;
	}
	if (Ample == nullptr) {
		return;
	}


	AHorrorProtoKimchiCharacter* Player = Cast<AHorrorProtoKimchiCharacter>(GetOwner());

	if (Player == nullptr) {
		LogHelper::PrintOnly(GetWorld(), "플레이어 캐스팅 안됨 오류");
		return;
	}

	SelectedAmple = Ample;

	UArrowComponent* handPosComponent = Player->HandposComponent;

	SelectedAmple->AttachToComponent(handPosComponent, FAttachmentTransformRules::KeepRelativeTransform);

	SelectedAmple->SetActorLocation(handPosComponent->GetComponentLocation() + FVector(0, 0, -20));
}

void UC_DocLevelComponent::NurseLeave()
{
	--CurrentNurseCount;
	if (CurrentNurseCount < 0) {
		LogHelper::PrintOnly(GetWorld(), "간호사 0 이하로 덜어짐");
	}
}

void UC_DocLevelComponent::UseAmple()
{
	bOnAmple = false;
	SelectedSyringe->Destroy();
	SelectedSyringe = nullptr;
}

void UC_DocLevelComponent::WasteSyringe()
{
	if (SelectedSyringe != nullptr) {
		SelectedSyringe->Destroy();
		SelectedSyringe = nullptr;
	}
}


