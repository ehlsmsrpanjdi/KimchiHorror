// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C_StateEnum.h"
#include "C_EntityBase.generated.h"


class UC_StateMachine;
class UC_StateBase;

UCLASS()
class HORRORPROTOKIMCHI_API AC_EntityBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_EntityBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void StateInit();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UC_StateMachine* entityStateMachine;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	C_StateEnum currentStateEnum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* doorCollision;


public:
	void ChangeState(C_StateEnum _stateEnum);

	void AddState(C_StateEnum _Enum, UC_StateBase* _BaseState);


public:
	UFUNCTION(BlueprintCallable)
	void SetActiveFalse();

	UFUNCTION(BlueprintCallable)
	void SetActiveTrue();

public:
	UFUNCTION(BlueprintCallable)
	void OnPlayerChaseMode();

	bool IsDoubtMax;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsNpc;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void JumpScare();
	virtual void JumpScare_Implementation();

	//의심도 연출용 재정의함수
	UFUNCTION(BlueprintImplementableEvent, Category = "Noise")
	 void SetNoise(int32 Doubt);

	
};
