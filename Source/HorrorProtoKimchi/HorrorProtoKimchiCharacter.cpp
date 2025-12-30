// Copyright Epic Games, Inc. All Rights Reserved.

#include "HorrorProtoKimchiCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Components/BoxComponent.h"
#include "Interaction/InteractionInterface.h"
#include "Debug/LogHelper.h"
#include "HorrorProtoKimchi.h"
#include "Doubt/C_DoubtsManager.h"
#include "Entity/C_EntityBase.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"
#include "C_QuestComponent.h"

AHorrorProtoKimchiCharacter::AHorrorProtoKimchiCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	TargetComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("TargetArrow"));
	TargetComponent->SetupAttachment(RootComponent);

	soundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("PlayerSoundComponent"));
	soundComponent->SetupAttachment(RootComponent);
}

void AHorrorProtoKimchiCharacter::BeginPlay()
{
	Super::BeginPlay();
	ActorsToIgnore.Add(this);

	QuestComponent = FindComponentByClass<UC_QuestComponent>();

	if (QuestComponent == nullptr) {
		LogHelper::PrintOnly(this, "QuestComponentIsNull");
	}

	if (MyGameInstance == nullptr) {
		MyGameInstance = Cast<UC_GameInstance>(GetGameInstance());
	}

	MyGameInstance->PlayerBeginPlay();
}

void AHorrorProtoKimchiCharacter::CheckInteraction()
{
	if (!FollowCamera) {
		return;
	}

	FVector Start = FollowCamera->GetComponentLocation();
	FVector End = Start + (FollowCamera->GetForwardVector() * 200);
	FHitResult Hit;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActors(ActorsToIgnore);
	QueryParams.bTraceComplex = false;

	bool bHit = GetWorld()->SweepSingleByChannel(
		Hit,
		Start,
		End,
		FQuat::Identity,
		InteractionChannel,
		FCollisionShape::MakeSphere(5.f),
		QueryParams
	);

	AActor* NewInteractActor = nullptr;

	if (bHit)
	{
		AActor* Actor = Hit.GetActor();
		if (Actor)
		{
			UPrimitiveComponent* HitComp = Hit.GetComponent();
			if (HitComp && HitComp->ComponentHasTag(FName("NoInteraction")))
			{
				// NoInteraction 태그 있으면 무시
			}
			else if (Actor->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
			{
				NewInteractActor = Actor;
			}
		}
	}

	// 상태 변화 감지 및 처리
	if (NewInteractActor != PreviousInteractActor)
	{
		// 이전 액터에게 CanNotInteract 호출
		if (PreviousInteractActor && PreviousInteractActor->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
		{
			IInteractionInterface::Execute_CanNotInteract(PreviousInteractActor, this);
		}
		// 새 액터에게 CanInteract 호출
		if (NewInteractActor)
		{
			IInteractionInterface::Execute_CanInteract(NewInteractActor, this);
		}
		PreviousInteractActor = NewInteractActor;
	}
	CurrentInteractActor = NewInteractActor;
}

void AHorrorProtoKimchiCharacter::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	currentInteractionTime += _DeltaTime;
	if (currentInteractionTime > InteractionTime) {
		CheckInteraction();
		currentInteractionTime -= InteractionTime;
	}
}

void AHorrorProtoKimchiCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHorrorProtoKimchiCharacter::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AHorrorProtoKimchiCharacter::Look);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AHorrorProtoKimchiCharacter::Look);

		EnhancedInputComponent->BindAction(InteractionAction, ETriggerEvent::Started, this, &AHorrorProtoKimchiCharacter::Interaction);

		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &AHorrorProtoKimchiCharacter::CrouchFunction);

	}


	else
	{
		UE_LOG(LogHorrorProtoKimchi, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AHorrorProtoKimchiCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// route the input
	DoMove(MovementVector.X, MovementVector.Y);
	PlayWalkSound();
}

void AHorrorProtoKimchiCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// route the input
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void AHorrorProtoKimchiCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void AHorrorProtoKimchiCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		this->PlayerYaw = Yaw;
		this->PlayerPitch = Pitch;
		// add yaw and pitch input to controller
		if (MyGameInstance != nullptr) {
			AddControllerYawInput(Yaw * MyGameInstance->MouseSensetive);
			AddControllerPitchInput(Pitch * MyGameInstance->MouseSensetive);
		}
		else {
			AddControllerYawInput(Yaw);
			AddControllerPitchInput(Pitch);
		}
	}
}

void AHorrorProtoKimchiCharacter::DoJumpStart()
{
	// signal the character to jump
	Jump();
}

void AHorrorProtoKimchiCharacter::DoJumpEnd()
{
	// signal the character to stop jumping
	StopJumping();
}

void AHorrorProtoKimchiCharacter::Interaction(const FInputActionValue& Value)
{
	DoInteraction();
}

void AHorrorProtoKimchiCharacter::DoInteraction()
{
	UE_LOG(LogTemp, Warning, TEXT("Interaction Attempt"));

	if (CurrentInteractActor != nullptr) {
		if (QuestComponent && IInteractionInterface::Execute_IsQuestObject(CurrentInteractActor, this))
		{
			FName QuestLine = IInteractionInterface::Execute_GetCurrentQuestLineName(CurrentInteractActor, this);

			IInteractionInterface::Execute_SetQuestComplete(CurrentInteractActor, this);
			NotifyQuestComponent(QuestLine);
		}
		// 상호작용 실행
		IInteractionInterface::Execute_OnInteract(CurrentInteractActor, this);
	}
}

void AHorrorProtoKimchiCharacter::CrouchFunction(const FInputActionValue& _Value)
{
	DoCrouchFunction();
}

void AHorrorProtoKimchiCharacter::DoCrouchFunction()
{
}

FVector AHorrorProtoKimchiCharacter::GetTargetPos()
{
	return TargetComponent->GetComponentLocation();
}


bool AHorrorProtoKimchiCharacter::AddDoubt(float _Value)
{
	if (alreadyMax == true) {
		return true;
	}
	CurrentDoubtGauge += _Value;
	UC_DoubtsManager* manager = UC_DoubtsManager::GetDoubtsManager(this);
	manager->SetDoubt(CurrentDoubtGauge);

	return false;
}

bool AHorrorProtoKimchiCharacter::IsDoubtMode()
{
	return MaxDoubtGauge <= CurrentDoubtGauge;
}

bool AHorrorProtoKimchiCharacter::PlayerTakeDamage(float _Value)
{
	CurrentHp -= _Value;
	if (CurrentHp <= 0) {
		return true;
	}
	return false;
}

void AHorrorProtoKimchiCharacter::PlayWalkSound()
{
	if (soundComponent == nullptr) {
		return;
	}
	if (soundComponent->IsPlaying() == true) {
		return;
	}
	if (walkSoundArray.Num() == 0) {
		return;
	}

	int32 RandomIndex = FMath::RandRange(0, walkSoundArray.Num() - 1);


	USoundBase* sound = walkSoundArray[RandomIndex];

	soundComponent->SetSound(sound);

	soundComponent->Play();
}

void AHorrorProtoKimchiCharacter::NotifyQuestComponent(FName _CurrentQuestLine)
{
	if (QuestComponent != nullptr && true == QuestComponent->CheckQuestLine(_CurrentQuestLine)) {
		QuestComponent->ExecuteQuest(_CurrentQuestLine);
	}
}
