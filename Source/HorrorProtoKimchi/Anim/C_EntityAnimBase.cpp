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
	case C_EntityMoveEnum::LookDown:
		Index = 2;
		break;
	case C_EntityMoveEnum::MadStand:
		Index = 3;
		break;
	case C_EntityMoveEnum::Run:
		Index = 4;
		break;
	case C_EntityMoveEnum::Dance:
		Index = 5;
		break;

	case C_EntityMoveEnum::CatWalk :

		Index =6 ;
		break;

	case C_EntityMoveEnum::LeftTurn:

		Index = 7;
		break;
	case C_EntityMoveEnum::RightTurn:

		Index = 8;
		break;
	case C_EntityMoveEnum::WalkLeftTurn:

		Index = 9;
		break;
	case C_EntityMoveEnum::WalkRightTurn:

		Index = 10;
		break;
	case C_EntityMoveEnum::BackWalk:

		Index = 11;
		break;
	case C_EntityMoveEnum::Talk1:

		Index =12 ;
		break;
	case C_EntityMoveEnum::Talk2:

		Index = 13;
		break;
	case C_EntityMoveEnum::Talk3:

		Index = 14;
		break;
	case C_EntityMoveEnum::Yelling:

		Index = 15;
		break;
	case C_EntityMoveEnum::NinjaRun:

		Index = 16;
		break;

	case C_EntityMoveEnum::MadSit:

		Index = 17;
		break;

	case C_EntityMoveEnum::MadLie:

		Index = 18;
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


