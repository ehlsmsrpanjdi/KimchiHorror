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
#include "Entity/C_EntityBase.h"

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

	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionBox->SetupAttachment(RootComponent);

	InteractionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractionBox->SetCollisionObjectType(ECC_WorldDynamic);
	InteractionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	InteractionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	InteractionBox->SetGenerateOverlapEvents(true);

	DoubtBox = CreateDefaultSubobject<UBoxComponent>(TEXT("DoubtBox"));
	DoubtBox->SetupAttachment(RootComponent);

	DoubtBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	DoubtBox->SetCollisionObjectType(ECC_WorldDynamic);
	DoubtBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	DoubtBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);


	TargetComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("TargetArrow"));
	TargetComponent->SetupAttachment(RootComponent);
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
		// add yaw and pitch input to controller
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
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

	if (CurrentInteractActor &&
		CurrentInteractActor->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
	{
		IInteractionInterface::Execute_OnInteract(CurrentInteractActor, this);
	}
}

void AHorrorProtoKimchiCharacter::CrouchFunction(const FInputActionValue& _Value)
{
	DoCrouchFunction();
}

void AHorrorProtoKimchiCharacter::DoCrouchFunction()
{
	LogHelper::PrintOnly(this, TEXT("crouch 눌림"));
}

FVector AHorrorProtoKimchiCharacter::GetTargetPos()
{
	return TargetComponent->GetComponentLocation();
}

void AHorrorProtoKimchiCharacter::OnInteractionBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		if (OtherActor->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
		{
			CurrentInteractActor = OtherActor;
			UE_LOG(LogTemp, Warning, TEXT("Interaction Target Found: %s"), *OtherActor->GetName());  // ⭐ 수정
		}
	}
}

void AHorrorProtoKimchiCharacter::OnInteractionEndOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this)
	{
		if (OtherActor == CurrentInteractActor)
		{
			CurrentInteractActor = nullptr;
			UE_LOG(LogTemp, Warning, TEXT("Interaction Target Removed"));  // 수정
		}
	}
}

bool AHorrorProtoKimchiCharacter::AddDoubt(float _Value)
{
	CurrentDoubtGauge += _Value;
	if (MaxDoubtGauge <= CurrentDoubtGauge) {
		for (AC_EntityBase* entity : EntityArray) {
			entity->OnPlayerChaseMode();
		}
		return true;
	}d
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

void AHorrorProtoKimchiCharacter::OnDoubtBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr) {
		AC_EntityBase* entity = Cast<AC_EntityBase>(OtherActor);
		if (entity == nullptr) {
			return;
		}
		if (IsDoubtMode() == true) {
			entity->OnPlayerChaseMode();
		}
		EntityArray.Add(entity);
	}
}

void AHorrorProtoKimchiCharacter::OnDoubtBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != nullptr) {
		AC_EntityBase* entity = Cast<AC_EntityBase>(OtherActor);
		EntityArray.Remove(entity);
	}
}
