// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/DocLevel/C_SyringeBox.h"
#include "Entity/DocLevel/C_DocLevelComponent.h"
#include "Debug/LogHelper.h"
#include "Entity/DocLevel/C_Syringe.h"
#include "HorrorProtoKimchiCharacter.h"

// Sets default values
AC_SyringeBox::AC_SyringeBox()
{

}


void AC_SyringeBox::InteractionEvent() {

	ACharacter* Character = GetWorld()->GetFirstPlayerController()->GetCharacter();

	UC_DocLevelComponent* DocComponent = Character->GetComponentByClass<UC_DocLevelComponent>();

	if (DocComponent == nullptr) {
		LogHelper::PrintOnly(this, "지금 플레이어한테 컴포넌트 없음");
	}

	if (DocComponent->SelectedSyringe != nullptr) {
		return;
	}

	if (DocComponent->SelectedAmple != nullptr) {
		return;
	}

	FTransform Transform;

	// Location
	Transform.SetLocation(FVector::ZeroVector);

	// Rotation (Pitch, Yaw, Roll)
	Transform.SetRotation(FQuat(FRotator(0.f, 0.f, 0.f)));

	// Scale
	Transform.SetScale3D(FVector(1.f, 1.f, 1.f));

	if (DocComponent->SelectedSyringe == nullptr && DocComponent->SelectedAmple == nullptr) {
		AActor* spawnedActor = GetWorld()->SpawnActor(SyringeClass, &Transform);

		AC_Syringe* syringe = Cast<AC_Syringe>(spawnedActor);

		if (syringe == nullptr) {
			return;
		}

		AHorrorProtoKimchiCharacter* Player = Cast<AHorrorProtoKimchiCharacter>(Character);

		if (Player == nullptr) {
			return;
		}

		syringe->AttachToComponent(Player->HandposComponent, FAttachmentTransformRules::KeepRelativeTransform);

		syringe->SetActorLocation(Player->HandposComponent->GetComponentLocation());

		syringe->SetActorRelativeRotation(FQuat(FRotator(0.f, 0.f, 90.f)));

		DocComponent->SelectedSyringe = syringe;
	}

}