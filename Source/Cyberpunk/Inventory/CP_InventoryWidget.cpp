#include "CP_InventoryWidget.h"

void UCP_InventoryWidget::UpdateInventory(const TArray<FCP_ItemInfo>& Items)
{
    if (!overlay00 || !overlay01 || !overlay02 || !overlay03 ||
        !overlay10 || !overlay11 || !overlay12 || !overlay13)
    {
        UE_LOG(LogTemp, Error, TEXT("[UpdateInventory] One or more UI elements are nullptr!"));
        return;
    }

    UE_LOG(LogTemp, Log, TEXT("[UpdateInventory] Updating inventory UI..."));

    // �迭�� UI ��ҵ��� �����Ͽ� �ڵ� ����ȭ
    TArray<UOverlay*> Overlays = { overlay00, overlay01, overlay02, overlay03,
                                   overlay10, overlay11, overlay12, overlay13 };

    TArray<UImage*> Images = { Image_00, Image_01, Image_02, Image_03,
                               Image_10, Image_11, Image_12, Image_13 };

    TArray<UTextBlock*> TextBlocks = { textblock00, textblock01, textblock02, textblock03,
                                       textblock10, textblock11, textblock12, textblock13 };

    // **�ʱ⿡�� ��� UI�� ����**
    if (Items.Num() == 0)
    {
        for (int32 i = 0; i < 8; i++)
        {
            Overlays[i]->SetVisibility(ESlateVisibility::Hidden);
            Images[i]->SetVisibility(ESlateVisibility::Hidden);
            TextBlocks[i]->SetVisibility(ESlateVisibility::Hidden);
        }
        UE_LOG(LogTemp, Log, TEXT("[UpdateInventory] Inventory is empty. UI remains hidden."));
        return;
    }

    // **��� ������ �ʱ�ȭ (�� ������ ����)**
    for (int32 i = 0; i < 8; i++)
    {
        Overlays[i]->SetVisibility(ESlateVisibility::Hidden);
        Images[i]->SetVisibility(ESlateVisibility::Hidden);
        TextBlocks[i]->SetVisibility(ESlateVisibility::Hidden);
        TextBlocks[i]->SetText(FText::FromString(""));
    }

    // **�κ��丮 �������� UI�� ǥ��**
    for (int32 i = 0; i < Items.Num() && i < 8; i++)
    {
        const FCP_ItemInfo& Item = Items[i];

        if (Item.ItemIcon)
        {
            // ������ ����
            FSlateBrush Brush;
            Brush.SetResourceObject(Item.ItemIcon);
            Brush.ImageSize = FVector2D(128.0f, 128.0f); // ������ ũ�� ����
            Images[i]->SetBrush(Brush);
            Images[i]->SetVisibility(ESlateVisibility::Visible);

            // Overlay ���̰� ����
            Overlays[i]->SetVisibility(ESlateVisibility::Visible);
        }

        if (Item.StackCount > 1)
        {
            TextBlocks[i]->SetText(FText::Format(FText::FromString("x{0}"), Item.StackCount));
            TextBlocks[i]->SetVisibility(ESlateVisibility::Visible);
        }
    }

    UE_LOG(LogTemp, Log, TEXT("[UpdateInventory] Inventory UI updated! Items displayed: %d"), Items.Num());
}
