// Fill out your copyright notice in the Description page of Project Settings.
#include "UI/C_UIManager.h"
#include "Kismet/GameplayStatics.h"

void UC_UIManager::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    UE_LOG(LogTemp, Log, TEXT("UIManager Initialized"));
}

void UC_UIManager::Deinitialize()
{
    UIDictionary.Empty();
    Super::Deinitialize();
}

UC_UIManager* UC_UIManager::GetUIManager(const UObject* WorldContextObject)
{
    if (!WorldContextObject) return nullptr;

    UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);
    if (!GameInstance) return nullptr;

    return GameInstance->GetSubsystem<UC_UIManager>();
}

void UC_UIManager::AddUI(TSubclassOf<UUserWidget> UIClass, UUserWidget* UIWidget)
{
    if (!UIClass || !UIWidget)
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid UI Class or Widget"));
        return;
    }

    if (UIDictionary.Contains(UIClass))
    {
        UE_LOG(LogTemp, Warning, TEXT("UI already exists, replacing: %s"), *UIClass->GetName());
        UIDictionary[UIClass] = UIWidget;
        return;
    }

    UIDictionary.Add(UIClass, UIWidget);
    UE_LOG(LogTemp, Log, TEXT("UI Added: %s"), *UIClass->GetName());
}

UUserWidget* UC_UIManager::GetUI(TSubclassOf<UUserWidget> UIClass)
{
    if (!UIClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid UI Class"));
        return nullptr;
    }

    UUserWidget** FoundUI = UIDictionary.Find(UIClass);
    if (!FoundUI || !*FoundUI)
    {
        UE_LOG(LogTemp, Warning, TEXT("UI not found: %s"), *UIClass->GetName());
        return nullptr;
    }

    return *FoundUI;
}

bool UC_UIManager::OnUI(TSubclassOf<UUserWidget> UIClass)
{
    UUserWidget* UI = GetUI(UIClass);
    if (UI)
    {
        UI->SetVisibility(ESlateVisibility::Visible);
        UI->AddToViewport();
        return true;
    }
    return false;
}

bool UC_UIManager::OffUI(TSubclassOf<UUserWidget> UIClass)
{
    UUserWidget* UI = GetUI(UIClass);
    if (UI)
    {
        UI->SetVisibility(ESlateVisibility::Hidden);
        UI->RemoveFromParent();
        return true;
    }
    return false;
}

UUserWidget* UC_UIManager::CreateAndAddUI(const UObject* WorldContextObject, TSubclassOf<UUserWidget> UIClass)
{
    if (!UIClass || !WorldContextObject)
    {
        return nullptr;
    }

    UUserWidget* NewWidget = CreateWidget<UUserWidget>(WorldContextObject->GetWorld(), UIClass);
    if (NewWidget)
    {
        AddUI(UIClass, NewWidget);
    }

    return NewWidget;
}