#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Sound/SoundBase.h" 
#include "Components/Button.h"
#include "Inventory/CP_Inventory.h"
#include "Guns/CP_BarrelInfo.h"
#include "Guns/CP_TriggerInfo.h"
#include "Guns/CP_BodyInfo.h"
#include "Guns/CP_GunTypes.h"
#include "Components/TextBlock.h"
#include "CP_CraftingMenuWidget.generated.h"

class ACP_Player;

UCLASS()
class CYBERPUNK_API UCP_CraftingMenuWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UCP_CraftingMenuWidget(const FObjectInitializer& ObjectInitializer);
    void SetInventoryReference(UCP_Inventory* Inventory);
protected:
    virtual void NativeConstruct() override;
    virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;  // ��Ŭ�� ����

    // UMG ���� ���ε�
    UPROPERTY(meta = (BindWidget))
    UButton* BarrelButton1;
    UPROPERTY(meta = (BindWidget))
    UButton* BarrelButton2;
    UPROPERTY(meta = (BindWidget))
    UButton* BarrelButton3;
    UPROPERTY(meta = (BindWidget))
    UButton* TriggerButton1;
    UPROPERTY(meta = (BindWidget))
    UButton* TriggerButton2;
    UPROPERTY(meta = (BindWidget))
    UButton* TriggerButton3;
    UPROPERTY(meta = (BindWidget))
    UButton* BodyButton1;
    UPROPERTY(meta = (BindWidget))
    UButton* BodyButton2;
    UPROPERTY(meta = (BindWidget))
    UButton* BodyButton3;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* ItemName;
    UPROPERTY(meta = (BindWidget))
    UTextBlock* ItemDescription;


private:
    // ��Ŭ�� ��� (������ ���� ǥ��)
    UFUNCTION()
    void OnBarrelButton1Clicked();
    UFUNCTION()
    void OnBarrelButton2Clicked();
    UFUNCTION()
    void OnBarrelButton3Clicked();
    UFUNCTION()
    void OnTriggerButton1Clicked();
    UFUNCTION()
    void OnTriggerButton2Clicked();
    UFUNCTION()
    void OnTriggerButton3Clicked();
    UFUNCTION()
    void OnBodyButton1Clicked();
    UFUNCTION()
    void OnBodyButton2Clicked();
    UFUNCTION()
    void OnBodyButton3Clicked();

    // ��Ŭ�� ��� (���� �� �߰� ���)
    void OnRightClickPart(UButton* ClickedButton);

    UCP_Inventory* InventoryRef = nullptr;

    void PlayEquipSound(bool bSuccess); 

    UPROPERTY(EditAnywhere, Category = "Sound")
    USoundBase* EquipSuccessSound;  

    UPROPERTY(EditAnywhere, Category = "Sound")
    USoundBase* EquipFailSound;  

    void UpdateItemInfo(const FString& Name, const FString& Description);
    void HandleCraftingFail();

    TMap<UButton*, FString> ButtonPartMap;  //  ��ư�� ���� �̸��� ����
};
