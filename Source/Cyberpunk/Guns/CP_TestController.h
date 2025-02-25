#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Inventory/CP_Inventory.h"
#include "Inventory/CP_InventoryWidget.h"
#include "CP_TestController.generated.h"

UCLASS()
class CYBERPUNK_API ACP_TestController : public APlayerController
{
    GENERATED_BODY()

public:
    ACP_TestController();

protected:
    virtual void BeginPlay() override;

    /** �÷��̾��� �κ��丮 */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
    UCP_Inventory* PlayerInventory;

    /** �κ��丮 ���� Ŭ���� (�������Ʈ���� ����) */
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UCP_InventoryWidget> InventoryWidgetClass;

    /** ������ ������ �κ��丮 ���� */
    UPROPERTY()
    UCP_InventoryWidget* InventoryWidget;
};
