// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_QuestComponent.generated.h"


UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class HORRORPROTOKIMCHI_API UC_QuestComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UC_QuestComponent();

	UFUNCTION(BlueprintCallable)
	virtual bool CheckQuestLine(FName _CurrentSelectedQuestObjName);

	// QuestComponent.h
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ExecuteQuest(FName _CurrentQuestLine);

	// C++에서 기본 구현 제공
	virtual void ExecuteQuest_Implementation(FName _CurrentQuestLine);


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName CurrentQuestLine;

	UFUNCTION(BlueprintCallable)
	void SetNextQuestLine(FName _NextQuestLine);
};
