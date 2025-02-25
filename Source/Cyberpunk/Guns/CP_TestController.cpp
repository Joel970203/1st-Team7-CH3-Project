#include "CP_TestController.h"
#include "Inventory/CP_Inventory.h"
#include "CP_BarrelInfo.h"
#include "Blueprint/UserWidget.h"

ACP_TestController::ACP_TestController()
{
    // �κ��丮 ����
    PlayerInventory = CreateDefaultSubobject<UCP_Inventory>(TEXT("PlayerInventory"));
}

void ACP_TestController::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Warning, TEXT("[TestController] BeginPlay Called"));

    if (!PlayerInventory)
    {
        UE_LOG(LogTemp, Error, TEXT("[TestController] PlayerInventory is NULL in Controller!"));
        return;
    }

    // **�⺻ ������ �߰� (������)**
    PlayerInventory->AddItem(ACP_BarrelInfo::StaticClass());

    UE_LOG(LogTemp, Warning, TEXT("[TestController] PlayerInventory Initialized with %d items"), PlayerInventory->Items.Num());

    // **UI ����**
    if (InventoryWidgetClass)
    {
        InventoryWidget = CreateWidget<UCP_InventoryWidget>(this, InventoryWidgetClass);
        if (InventoryWidget)
        {
            InventoryWidget->AddToViewport();

            // **���⼭ �κ��丮�� ������ ����!**
            InventoryWidget->SetPlayerInventory(PlayerInventory);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("[TestController] Failed to create InventoryWidget!"));
        }
    }
}
