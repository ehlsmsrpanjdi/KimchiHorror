// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/Stage_1/Child/C_HideChild.h"
#include "C_KimchiHelper.h"
#include "HorrorProtoKimchiCharacter.h"
#include "Components/ArrowComponent.h"
#include "Components/SceneComponent.h"

bool AC_HideChild::MoveFunction()
{
	if (FindPlayer == false) {
		if (Player->IsHide == false) {
			return UC_KimchiHelper::MoveToLocationAndCheckArrival(this, Player->GetActorLocation(), 50.f);
		}
		if (Player->IsHide == true) {
			return UC_KimchiHelper::MoveToLocationAndCheckArrival(this, locationComponent->GetComponentLocation(), 50.f);
		}

		if (locationComponent == nullptr) {
			return false;
		}
		return false;
	}
	else {
		return UC_KimchiHelper::MoveToLocationAndCheckArrival(this, Player->GetActorLocation(), 50.f);
	}
}

//void AC_HideChild::CheckFindPlayer()
//{
//	FHitResult result = UC_KimchiHelper::LineTraceActorToActor(this, Player, false);
//
//	if (result.GetActor() == nullptr) {
//		return;
//	}
//	if (Player == result.GetActor()) {
//		FindPlayer = true;
//	}
//}

bool AC_HideChild::CheckCoolTime(float _Deltatime)
{
	currentActiveTime += _Deltatime;
	if (currentActiveTime > activeTime) {
		currentActiveTime -= activeTime;
		return true;
	}
	else {
		return false;
	}

}

