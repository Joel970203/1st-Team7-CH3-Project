#include "CP_InventoryWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UCP_InventoryWidget::NativeConstruct()
{
    Super::NativeConstruct();
}

void UCP_InventoryWidget::UpdateInventory(const TArray<FCP_ItemInfo>& Items)
{
    if (!InventoryGrid) return;

    // ���� UI ����
    InventoryGrid->ClearChildren();

    int32 SlotIndex = 0;
    for (const FCP_ItemInfo& Item : Items)
    {
        // UI���� ���ο� ��ư�� �������� ����
        UButton* ItemButton = NewObject<UButton>(this);
        UImage* ItemIcon = NewObject<UImage>(this);
        UTextBlock* ItemName = NewObject<UTextBlock>(this);

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
}
