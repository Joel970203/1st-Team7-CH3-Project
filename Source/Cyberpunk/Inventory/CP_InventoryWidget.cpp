#include "CP_InventoryWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UCP_InventoryWidget::NativeConstruct()
{
    Super::NativeConstruct();

}

void UCP_InventoryWidget::UpdateInventory(const TArray<FCP_ItemInfo>& Items)
{
    if (!InventoryGrid)
    {
        UE_LOG(LogTemp, Error, TEXT("[UpdateInventory] InventoryGrid nullptr!"));
        return;
    }

    // ���� UI ���� ����
    InventoryGrid->ClearChildren();

    UE_LOG(LogTemp, Log, TEXT("[UpdateInventory] updated started: %d"), Items.Num());

    int32 SlotIndex = 0;
    for (const FCP_ItemInfo& Item : Items)
    {
        UE_LOG(LogTemp, Log, TEXT("[UpdateInventory] slot added: %s"), *Item.ItemName);

        // UI���� ���ο� ��ư�� �������� ����
        UButton* ItemButton = NewObject<UButton>(this);
        UImage* ItemIcon = NewObject<UImage>(this);
        UTextBlock* ItemName = NewObject<UTextBlock>(this);


        FSlateBrush Brush;
        Brush.SetResourceObject(Item.ItemIcon);
        Brush.ImageSize = FVector2D(64.0f, 64.0f); // ������ ũ�� Ű���

        ItemIcon->SetBrush(Brush);

        //  ��ư ũ�� ���� (���� ũ�� ���� ����)
        ItemButton->SetRenderTransform(FWidgetTransform(FVector2D(0, 0), FVector2D(1.5f, 1.5f), FVector2D(0, 0), 0.0f));

        // ������ ����
        if (Item.ItemIcon)
        {
            ItemIcon->SetBrushFromTexture(Item.ItemIcon);
        }

        // ������ �̸� ����
        ItemName->SetText(FText::FromString(Item.ItemName));

        // ��ư�� ������ �߰�
        ItemButton->AddChild(ItemIcon);

        // ���� �гο� ��ư �߰�
        InventoryGrid->AddChildToUniformGrid(ItemButton, SlotIndex / 4, SlotIndex % 4);

        SlotIndex++;
        if (SlotIndex >= 8) break; // 8ĭ������ ���
    }

    UE_LOG(LogTemp, Log, TEXT("[UpdateInventory] Inventory updated!"));
}


