#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "CP_PlayerHUD.generated.h"

UCLASS()
class CYBERPUNK_API UCP_PlayerHUD : public UUserWidget
{
    GENERATED_BODY()

public:
    UCP_PlayerHUD(const FObjectInitializer& ObjectInitializer);

    // HUD ������Ʈ �Լ�
    UFUNCTION(BlueprintCallable, Category = "HUD")
    void UpdateHUD(int32 Wave, const FString& WeaponName, int32 Ammo, int32 Health, int32 EnemiesRemaining);

protected:
    virtual void NativeConstruct() override;

    // UMG ���� ���ε�
    UPROPERTY(meta = (BindWidget))
    UTextBlock* WaveText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* WeaponNameText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* AmmoText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* HealthText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* EnemiesRemainingText;
};
