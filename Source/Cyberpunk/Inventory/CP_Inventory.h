#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CP_ItemInfo.h"
#include "Guns/CP_TriggerInfo.h"
#include "CP_Inventory.generated.h"

class ACP_Guns;
class ACP_Player;
UCLASS(Blueprintable, BlueprintType)
class CYBERPUNK_API UCP_Inventory : public UObject
{
    GENERATED_BODY()

public:
    //������ �߰� 
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void AddItem(const FCP_ItemInfo& NewItem);

    void Initialize(AActor* InOwner);

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

    UPROPERTY()
    AActor* Owner;
};
