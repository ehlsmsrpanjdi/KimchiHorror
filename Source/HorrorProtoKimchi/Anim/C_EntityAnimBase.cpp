// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/C_EntityAnimBase.h"



void UC_EntityAnimBase::SetBodyMove(C_EntityMoveEnum pose)
{
	switch (pose)
	{
	case C_EntityMoveEnum::Idle  :
		Index = 0;
		break;
	case C_EntityMoveEnum::Walk :
		Index = 1;
		break;
	case C_EntityMoveEnum::Run:
		Index = 2;
		break;
	case C_EntityMoveEnum::Dance:
		Index = 3;
		break;

	default :
		Index = 0;
		break;
	}


}

void UC_EntityAnimBase::LerfTiltHead(FVector des, float speed)
{
	TiltHead = TargetHeadTilt;
	TiltSpeed = speed;
	TargetHeadTilt = des;

}

void UC_EntityAnimBase::NativeUpdateAnimation(float DeltaSeconds)
{
	
		Super::NativeUpdateAnimation(DeltaSeconds);


		TiltHead = FMath::VInterpTo(
			TiltHead,
			TargetHeadTilt,
			DeltaSeconds,
			TiltSpeed
		);
		/*GEngine->AddOnScreenDebugMessage((uint64)this, 0.f, FColor::Green,
			FString::Printf(TEXT("AnimTick %s"), *GetNameSafe(GetSkelMeshComponent())));*/
}


