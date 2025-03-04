#include "CP_InventoryWidget.h"
#include "CP_Inventory.h"

void UCP_InventoryWidget::NativeConstruct()
{
    Super::NativeConstruct();
    BindRightClickEvents();
}

void UCP_InventoryWidget::BindRightClickEvents()
{
    InventoryButtons = { Button_00, Button_01, Button_02, Button_03,
                         Button_10, Button_11, Button_12, Button_13 };

    for (int32 i = 0; i < InventoryButtons.Num(); i++)
    {
        if (InventoryButtons[i])
        {
            ButtonSlotMap.Add(InventoryButtons[i], i);
        }
    }
}

FReply UCP_InventoryWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
    {

        // InventoryRef ��ȿ�� üũ
        if (!InventoryRef)
        {
            return FReply::Handled();
        }

        // ���� ���콺�� � ��ư ���� �ִ��� Ȯ��
        for (auto& Pair : ButtonSlotMap)
        {
            UButton* Button = Pair.Key;
            if (Button && Button->IsHovered()) // ���� ���콺�� �ش� ��ư ���� �ִ��� Ȯ��
            {
                int32 SlotIndex = Pair.Value;
                if (SlotIndex < 0 || SlotIndex >= CurrentItems.Num())
                {
                    return FReply::Handled();
                }

                const FCP_ItemInfo& SelectedItem = CurrentItems[SlotIndex];

                if (InventoryRef)
                {
                    InventoryRef->UseItem(SelectedItem);
                }

                return FReply::Handled();
            }
        }
    }

    return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void UCP_InventoryWidget::SetInventoryReference(UCP_Inventory* Inventory)
{
    if (!Inventory)
    {
        UE_LOG(LogTemp, Error, TEXT("[UCP_InventoryWidget] Passed Inventory is nullptr!"));
        return;
    }

    InventoryRef = Inventory;
    UE_LOG(LogTemp, Log, TEXT("[UCP_InventoryWidget] Inventory Reference Set: %s"), *Inventory->GetName());
}


void UCP_InventoryWidget::UpdateInventory(const TArray<FCP_ItemInfo>& Items)
{
    if (!overlay00 || !overlay01 || !overlay02 || !overlay03 ||
        !overlay10 || !overlay11 || !overlay12 || !overlay13)
    {
        return;
    }

    CurrentItems.Empty();

    // UI ��� �迭ȭ
    TArray<UOverlay*> Overlays = { overlay00, overlay01, overlay02, overlay03,
                                   overlay10, overlay11, overlay12, overlay13 };

    TArray<UImage*> Images = { Image_00, Image_01, Image_02, Image_03,
                               Image_10, Image_11, Image_12, Image_13 };

    TArray<UTextBlock*> TextBlocks = { textblock00, textblock01, textblock02, textblock03,
                                       textblock10, textblock11, textblock12, textblock13 };

    // �ʱ�ȭ: ��� ������ �⺻ ���·� ����
    for (int32 i = 0; i < 8; i++)
    {
        Overlays[i]->SetVisibility(ESlateVisibility::Visible); // ���� ����
        Images[i]->SetBrush(FSlateBrush()); // �� ���� ó��
        Images[i]->SetVisibility(ESlateVisibility::Hidden);
        TextBlocks[i]->SetVisibility(ESlateVisibility::Hidden);
        TextBlocks[i]->SetText(FText::FromString(""));
    }

    // **���� ������ �������� �����Ͽ� ǥ��**
    TMap<FName, FCP_ItemInfo> ItemMap;
    for (const FCP_ItemInfo& Item : Items)
    {
        FName ItemName = FName(*Item.ItemName);
        if (ItemMap.Contains(ItemName))
        {
            ItemMap[ItemName].StackCount += Item.StackCount;
        }
        else
        {
            ItemMap.Add(ItemName, Item);
        }
    }

    // ���� ������Ʈ
    int32 SlotIndex = 0;
    for (const auto& Pair : ItemMap)
    {
        if (SlotIndex >= 8) break;

        const FCP_ItemInfo& Item = Pair.Value;
        Overlays[SlotIndex]->SetVisibility(ESlateVisibility::Visible);

        if (Item.ItemIcon)
        {
            FSlateBrush Brush;
            Brush.SetResourceObject(Item.ItemIcon);
            Brush.ImageSize = FVector2D(128.0f, 128.0f);
            Images[SlotIndex]->SetBrush(Brush);
            Images[SlotIndex]->SetVisibility(ESlateVisibility::Visible);
        }

        if (Item.StackCount > 1)
        {
            TextBlocks[SlotIndex]->SetText(FText::Format(FText::FromString("x{0}"), Item.StackCount));
            TextBlocks[SlotIndex]->SetVisibility(ESlateVisibility::Visible);
        }

        // **CurrentItems�� �ùٸ� ������ ����**
        CurrentItems.Add(Item);
        UE_LOG(LogTemp, Warning, TEXT("[UCP_InventoryWidget] CurrentItems[%d]: %s"), SlotIndex, *Item.ItemName);

        SlotIndex++;
    }
}
