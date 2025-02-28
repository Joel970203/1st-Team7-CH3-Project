#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CP_ItemInfo.h"
#include "CP_Inventory.generated.h"

UCLASS(Blueprintable, BlueprintType)
class CYBERPUNK_API UCP_Inventory : public UObject
{
    GENERATED_BODY()

public:
    //������ �߰� 
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void AddItem(const FCP_ItemInfo& NewItem);

    // ������ ���� 
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void RemoveItem(const FCP_ItemInfo& ItemInfo);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool HasItem(const FString& ItemName) const;

    // ���� �κ��丮 ������ ����Ʈ ��ȯ 
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    TArray<FCP_ItemInfo> GetInventoryItems() const;

private:
    // ������ ���
    UPROPERTY()
    TArray<FCP_ItemInfo> InventoryItems;
};
