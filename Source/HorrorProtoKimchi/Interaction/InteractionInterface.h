#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractionInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

class IInteractionInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void OnInteract(AActor* Interactor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void CanNotInteract(AActor* Interactor);

	// 상호작용 가능 여부
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void CanInteract(AActor* Interactor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	bool IsQuestObject(AActor* Interactor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	FName GetCurrentQuestLineName(AActor* Interactor);

	virtual void CanInteract_Implementation(AActor* Interactor);

	virtual void OnInteract_Implementation(AActor* Interactor);

	virtual void CanNotInteract_Implementation(AActor* Interactor);

	virtual bool IsQuestObject_Implementation(AActor* Interactor);

	virtual FName GetCurrentQuestLineName_Implementation(AActor* Interactor);
};