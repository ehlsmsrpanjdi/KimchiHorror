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
    UClass* NativeClass = GetNativeClass(UIWidget->GetClass());

    if (!NativeClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to get native class"));
        return;
    }

    if (UIDictionary.Contains(NativeClass))
    {
        UE_LOG(LogTemp, Warning, TEXT("UI already exists, replacing: %s"), *NativeClass->GetName());
        UIDictionary[NativeClass] = UIWidget;
        return;
    }

    UIDictionary.Add(NativeClass, UIWidget);
    UE_LOG(LogTemp, Log, TEXT("UI Added with key: %s"), *NativeClass->GetName());
}

UUserWidget* UC_UIManager::GetUI(TSubclassOf<UUserWidget> UIClass)
{
    if (!UIClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid UI Class"));
        return nullptr;
    }

    // 핵심: 여기서도 GetNativeClass 사용!
    UClass* NativeClass = GetNativeClass(UIClass);
    if (!NativeClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to get native class"));
        return nullptr;
    }

    UUserWidget** FoundUI = UIDictionary.Find(NativeClass);
    if (!FoundUI || !*FoundUI)
    {
        UE_LOG(LogTemp, Warning, TEXT("UI not found: %s"), *NativeClass->GetName());
        return nullptr;
    }

    return *FoundUI;
}

bool UC_UIManager::OnUI(TSubclassOf<UUserWidget> UIClass)
{
    if (!UIClass) return false;

    UClass* NativeClass = GetNativeClass(UIClass);
    if (!NativeClass) return false;

    UUserWidget** FoundUI = UIDictionary.Find(NativeClass);
    if (FoundUI && *FoundUI)
    {
        (*FoundUI)->SetVisibility(ESlateVisibility::Visible);
        (*FoundUI)->AddToViewport();
        return true;
    }
    return false;
}

bool UC_UIManager::OffUI(TSubclassOf<UUserWidget> UIClass)
{
    if (!UIClass) return false;

    UClass* NativeClass = GetNativeClass(UIClass);
    if (!NativeClass) return false;

    UUserWidget** FoundUI = UIDictionary.Find(NativeClass);
    if (FoundUI && *FoundUI)
    {
        (*FoundUI)->SetVisibility(ESlateVisibility::Hidden);
        (*FoundUI)->RemoveFromParent();
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

    // 1) 위젯 생성
    UUserWidget* NewWidget =
        CreateWidget<UUserWidget>(WorldContextObject->GetWorld(), UIClass);

    if (!NewWidget)
    {
        return nullptr;
    }

    // 2) Viewport에 추가
    NewWidget->AddToViewport();

    // 3) 처음 생성 시 비활성화 (보이지 않게)
    NewWidget->SetVisibility(ESlateVisibility::Hidden);

    // 4) UIManager 내부 리스트에 저장
    AddUI(UIClass, NewWidget);

    return NewWidget;
}

UClass* UC_UIManager::GetNativeClass(UClass* InClass)
{
    if (!InClass) return nullptr;

    // Blueprint 클래스인 경우 C++ 부모 클래스 찾기
    UClass* CurrentClass = InClass;
    while (CurrentClass && CurrentClass->ClassGeneratedBy != nullptr)
    {
        CurrentClass = CurrentClass->GetSuperClass();
    }

    return CurrentClass;
}

void UC_UIManager::ClearDictionary()
{
    UIDictionary.Empty();
}
