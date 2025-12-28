#include "Anim/C_AnimBPBase.h"
#include "GameFramework/Pawn.h"
#include "Kismet/KismetMathLibrary.h"

void UC_AnimBPBase::SetFacePose(C_FacePoseEnum pose, C_FaceMoodEnum mood, float interval = 0.1f)
{
	switch (pose)
	{
	case C_FacePoseEnum::Idle:
		FirstIndex = 0;
		LastIndex = 0;
		break;
	case C_FacePoseEnum::Talk:
		FirstIndex = 1;
		LastIndex = 5;
		break;

	case C_FacePoseEnum::MadLaugh :
		FirstIndex = 6;
		LastIndex = 6;
	
	case C_FacePoseEnum::AngerYelling :
		FirstIndex = 7;
		LastIndex = 7;

	case C_FacePoseEnum::CloseEye :
		FirstIndex = 8;
		LastIndex = 8;
	default:
		break;
	}

	switch (mood)
	{
	case C_FaceMoodEnum::Normal:
		MoodIndex =0 ;
		break;
	case C_FaceMoodEnum::Joy:
		MoodIndex =1 ;
		break;

	case C_FaceMoodEnum::Anger:
		MoodIndex =2 ;
		break;
	case C_FaceMoodEnum::MadLaugh:
		MoodIndex = 3;
		break;
	case C_FaceMoodEnum:: MadCloseEye:
		MoodIndex = 4;
		break;
	default:
		break;
	}


	Interval = interval;
}



int32 UC_AnimBPBase::RandomIndex(int32 first, int32 last)
{

	int32 Value = FMath::RandRange(first, last);

	return Value;
}

void UC_AnimBPBase::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ElapsedTime += DeltaSeconds;
	
		if (ElapsedTime > Interval)
	{
		ElapsedTime = 0.f;
		PoseIndex = RandomIndex(FirstIndex,LastIndex); 
	}
	
}


