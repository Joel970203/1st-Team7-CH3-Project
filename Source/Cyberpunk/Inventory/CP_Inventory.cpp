#include "CP_Inventory.h"

void UCP_Inventory::AddItem(const FCP_ItemInfo& NewItem)
{
    // ���� ������ ã��
    FCP_ItemInfo* ExistingItem = InventoryItems.FindByPredicate([&](const FCP_ItemInfo& Item)
    {
        return Item.ItemName == NewItem.ItemName;
    });

    if (ExistingItem)
    {
        //  ���� �������̸� ������ ����
        ExistingItem->StackCount++;
        UE_LOG(LogTemp, Log, TEXT("[Inventory] item : %s | count : %d"), *ExistingItem->ItemName, ExistingItem->StackCount);
    }
    else
    {
        //  ���ο� �������̸� �߰�
        InventoryItems.Add(NewItem);
        UE_LOG(LogTemp, Log, TEXT("[Inventory] new item: %s"), *NewItem.ItemName);
    }
}


void UCP_Inventory::RemoveItem(const FString& ItemName)
{
    int32 Index = InventoryItems.IndexOfByPredicate([&](const FCP_ItemInfo& Item) {
        return Item.ItemName == ItemName;
    });

    if (Index != INDEX_NONE)
    {
        InventoryItems.RemoveAt(Index);
        UE_LOG(LogTemp, Log, TEXT("Item erased : %s"), *ItemName);
    }
}

bool UCP_Inventory::HasItem(const FString& ItemName) const
{
    return InventoryItems.ContainsByPredicate([&](const FCP_ItemInfo& Item) {
        return Item.ItemName == ItemName;
    });
}

TArray<FCP_ItemInfo> UCP_Inventory::GetInventoryItems() const
{
    return InventoryItems;
}
