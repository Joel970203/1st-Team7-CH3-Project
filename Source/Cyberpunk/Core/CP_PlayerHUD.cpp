#include "CP_PlayerHUD.h"
#include "Components/TextBlock.h"
#include "Math/Color.h" // FLinearColor�� ���� ������ ���� �ʿ�
#include "Guns/CP_Guns.h" // ACP_Guns Ŭ���� ����� ���� �ʿ�

UCP_PlayerHUD::UCP_PlayerHUD(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void UCP_PlayerHUD::NativeConstruct()
{
    Super::NativeConstruct();
    if (WaveText) WaveText->SetText(FText::AsNumber(0));
    //if (WeaponNameText) WeaponNameText->SetText(FText::FromString("No Weapon"));
    if (AmmoText) AmmoText->SetText(FText::AsNumber(0));
    if (MaxAmmoText) MaxAmmoText->SetText(FText::AsNumber(0)); // �ִ� ź�෮ �ʱⰪ ����
    if (HealthText) HealthText->SetText(FText::AsNumber(100));
    if (EnemiesRemainingText) EnemiesRemainingText->SetText(FText::AsNumber(0));
    if (KillCountText) KillCountText->SetText(FText::AsNumber(0)); // ųī��Ʈ �ʱⰪ ����
}

void UCP_PlayerHUD::UpdateWave(int32 Wave)
{
    if (WaveText)
    {
        WaveText->SetText(FText::AsNumber(Wave));
    }
}

void UCP_PlayerHUD::UpdateWeaponName(const FString& WeaponName)
{
    if (WeaponNameText)
    {
        WeaponNameText->SetText(FText::FromString(WeaponName));
    }
}

void UCP_PlayerHUD::UpdateAmmo(int32 Ammo)
{
    if (AmmoText)
    {
        // ���� ź�� �� �ؽ�Ʈ ������Ʈ
        AmmoText->SetText(FText::AsNumber(Ammo));

        // ź�� ���� ��� (0.0 ~ 1.0)
        float ammoRatio = static_cast<float>(Ammo);

        // ������� ���������� ���� ����
        FLinearColor newColor = FLinearColor::LerpUsingHSV(FLinearColor::White, FLinearColor::Red, 1.0f - ammoRatio);

        // ���� ����
        AmmoText->SetColorAndOpacity(newColor);
    }
}

void UCP_PlayerHUD::UpdateMaxAmmo(int32 MaxAmmo)
{
    if (MaxAmmoText)
    {
        MaxAmmoText->SetText(FText::AsNumber(MaxAmmo)); // �ִ� ź�෮ ������Ʈ
    }
}

void UCP_PlayerHUD::UpdateHealth(int32 Health, int32 MaxHealth)
{
    if (HealthText)
    {
        // ü�� �ؽ�Ʈ ������Ʈ
        HealthText->SetText(FText::AsNumber(Health));

        // ü�� ���� ��� (0.0 ~ 1.0)
        float healthRatio = static_cast<float>(Health) / static_cast<float>(MaxHealth);

        // ������� ���������� ���� ����
        FLinearColor newColor = FLinearColor::LerpUsingHSV(FLinearColor::White, FLinearColor::Red, 1.0f - healthRatio);

        // ���� ����
        HealthText->SetColorAndOpacity(newColor);
    }
}

void UCP_PlayerHUD::UpdateEnemiesRemaining(int32 EnemiesRemaining)
{
    if (EnemiesRemainingText)
    {
        EnemiesRemainingText->SetText(FText::AsNumber(EnemiesRemaining));
    }
}

void UCP_PlayerHUD::UpdateKillCount(int32 KillCount)
{
    if (KillCountText)
    {
        KillCountText->SetText(FText::AsNumber(KillCount)); // ųī��Ʈ ������Ʈ
    }
}

void SomeFunctionToUpdateHUD(UCP_PlayerHUD* PlayerHUD, ACP_Guns* Guns)
{
    if (PlayerHUD && Guns)
    {
        int32 CurrentAmmo = Guns->AmmoCount;
        int32 MaxAmmo = Guns->MaxAmmo;

        PlayerHUD->UpdateAmmo(CurrentAmmo);
        PlayerHUD->UpdateMaxAmmo(MaxAmmo);
    }
}