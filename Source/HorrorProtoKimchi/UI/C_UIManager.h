// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "C_UIManager.generated.h"

UCLASS()
class HORRORPROTOKIMCHI_API UC_UIManager : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    // 서브시스템 초기화
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    // 블루프린트에서 UIManager 얻기
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UI", meta = (WorldContext = "WorldContextObject"))
    static UC_UIManager* GetUIManager(const UObject* WorldContextObject);

    // UI 추가
    UFUNCTION(BlueprintCallable, Category = "UI")
    void AddUI(TSubclassOf<UUserWidget> UIClass, UUserWidget* UIWidget);

    // UI 가져오기
    UFUNCTION(BlueprintCallable, Category = "UI")
    UUserWidget* GetUI(TSubclassOf<UUserWidget> UIClass);

    // UI 켜기
    UFUNCTION(BlueprintCallable, Category = "UI")
    bool OnUI(TSubclassOf<UUserWidget> UIClass);

    // UI 끄기
    UFUNCTION(BlueprintCallable, Category = "UI")
    bool OffUI(TSubclassOf<UUserWidget> UIClass);

    // UI 생성 및 추가 (편의 함수)
    UFUNCTION(BlueprintCallable, Category = "UI", meta = (WorldContext = "WorldContextObject"))
    UUserWidget* CreateAndAddUI(const UObject* WorldContextObject, TSubclassOf<UUserWidget> UIClass);

private:
    UPROPERTY()
    TMap<TSubclassOf<UUserWidget>, UUserWidget*> UIDictionary;
}; 