#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CP_InventorySlot.h"
#include "CP_Inventory.h" 
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "CP_InventoryWidget.generated.h"

UCLASS()
class CYBERPUNK_API UCP_InventoryWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    /** �κ��丮 UI�� ������Ʈ�ϴ� �Լ� */
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void UpdateInventoryUI(const TArray<TSubclassOf<AActor>>& Items);
    virtual void NativeConstruct() override;

    /** �÷��̾� �κ��丮 ���� */
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void SetPlayerInventory(UCP_Inventory* NewInventory);
protected:
    /** ��� ���� ǥ�� */
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* GearStats;

    /** �κ��丮 ���� (8ĭ) */
    UPROPERTY(meta = (BindWidget))
    class UUniformGridPanel* InventoryGrid;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory")
    TSubclassOf<UCP_InventorySlot> InventorySlotClass;

    /** �÷��̾� �κ��丮 */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
    UCP_Inventory* PlayerInventory;


};
