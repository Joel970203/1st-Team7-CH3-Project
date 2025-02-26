#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include "CP_ItemInfo.generated.h"

/** ������ Ÿ���� �����ϴ� ������ */
UENUM(BlueprintType)
enum class ECP_ItemType : uint8
{
    Gear UMETA(DisplayName = "Gear"),
    Heal UMETA(DisplayName = "Heal"),
    Ammo UMETA(DisplayName = "Ammo"),
    GunPart UMETA(DisplayName = "GunPart")
};

/** �κ��丮�� ����� ������ ���� */
USTRUCT(BlueprintType)
struct FCP_ItemInfo
{
    GENERATED_BODY()

public:
    /** �������� Ÿ�� */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    ECP_ItemType ItemType;

    /** ������ �̸� */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FString ItemName;

    /** ������ ������ */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    UTexture2D* ItemIcon;

    /** �⺻ ������ */
    FCP_ItemInfo()
        : ItemType(ECP_ItemType::Gear), ItemName(TEXT("")), ItemIcon(nullptr) {}
};
