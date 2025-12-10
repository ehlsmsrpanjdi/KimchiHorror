#include "Anim/C_AnimBPBase.h"
#include "GameFramework/Pawn.h"
#include "Kismet/KismetMathLibrary.h"

void UC_AnimBPBase::SetFacePose(C_FacePoseEnum pose, float interval = 0.1f)
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
	case C_FacePoseEnum::Smile:
		FirstIndex = 0;
		LastIndex = 0;
		break;
	case C_FacePoseEnum::Anger:
		FirstIndex = 0;
		LastIndex = 0;
		break;
	case C_FacePoseEnum::Strange:
		FirstIndex = 0;
		LastIndex = 0;
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
		Index = RandomIndex(FirstIndex,LastIndex); 
	}
	
}


