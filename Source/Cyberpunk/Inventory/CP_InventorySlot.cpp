#include "CP_InventorySlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Guns/CP_Guns.h"
#include "Guns/CP_BarrelInfo.h"
#include "Guns/CP_BodyInfo.h"
#include "Guns/CP_TriggerInfo.h"

void UCP_InventorySlot::SetItem(const FString& NewItemName)
{
    ItemName = NewItemName;

    // UI�� ������ �̸� ǥ��
    if (ItemNameText)
    {
        ItemNameText->SetText(FText::FromString(NewItemName));
    }

    // ������ ã��
    UTexture2D* IconTexture = nullptr;

    /** �跲 Ŭ���� �˻� */
    for (TObjectIterator<UClass> It; It; ++It)
    {
        if (It->IsChildOf(ACP_BarrelInfo::StaticClass()))
        {
            ACP_BarrelInfo* DefaultBarrel = Cast<ACP_BarrelInfo>(It->GetDefaultObject());
            if (DefaultBarrel && DefaultBarrel->PartName == NewItemName)
            {
                IconTexture = DefaultBarrel->IconTexture;
                break;
            }
        }
    }

    /** �ٵ� Ŭ���� �˻� */
    if (!IconTexture)
    {
        for (TObjectIterator<UClass> It; It; ++It)
        {
            if (It->IsChildOf(ACP_BodyInfo::StaticClass()))
            {
                ACP_BodyInfo* DefaultBody = Cast<ACP_BodyInfo>(It->GetDefaultObject());
                if (DefaultBody && DefaultBody->PartName == NewItemName)
                {
                    IconTexture = DefaultBody->IconTexture;
                    break;
                }
            }
        }
    }

    /** Ʈ���� Ŭ���� �˻� */
    if (!IconTexture)
    {
        for (TObjectIterator<UClass> It; It; ++It)
        {
            if (It->IsChildOf(ACP_TriggerInfo::StaticClass()))
            {
                ACP_TriggerInfo* DefaultTrigger = Cast<ACP_TriggerInfo>(It->GetDefaultObject());
                if (DefaultTrigger && DefaultTrigger->PartName == NewItemName)
                {
                    IconTexture = DefaultTrigger->IconTexture;
                    break;
                }
            }
        }
    }

    /**������ ���� */
    if (IconTexture && ItemIcon)
    {
        ItemIcon->SetBrushFromTexture(IconTexture);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Icon not found for: %s"), *NewItemName);
    }
}
