#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CP_ItemInfo.h"
#include "CP_InventoryWidget.generated.h"

class UUniformGridPanel;
class UButton;

UCLASS()
class CYBERPUNK_API UCP_InventoryWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    /** �κ��丮 UI�� ������Ʈ */
    void UpdateInventory(const TArray<FCP_ItemInfo>& Items);

protected:
    virtual void NativeConstruct() override;

private:
    /** �κ��丮 ������ ��ġ�� �г� */
    UPROPERTY(meta = (BindWidget))
    UUniformGridPanel* InventoryGrid;

};
