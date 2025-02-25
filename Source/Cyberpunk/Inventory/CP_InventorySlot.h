#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "CP_InventorySlot.generated.h"

UCLASS()
class CYBERPUNK_API UCP_InventorySlot : public UUserWidget
{
    GENERATED_BODY()

public:
    /** ���Կ� ������ ���� */
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void SetItem(const FString& ItemName);

protected:
    /** ������ ������ */
    UPROPERTY(meta = (BindWidget))
    class UImage* ItemIcon;

    /** ������ �̸� */
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* ItemNameText;

    /** ������ ������ ������ �̸� */
    UPROPERTY(BlueprintReadOnly, Category = "Inventory")
    FString ItemName;

    /** ��Ŭ�� �̺�Ʈ ó�� */
    //virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
};
