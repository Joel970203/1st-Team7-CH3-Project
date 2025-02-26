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
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ItemName; // ������ �̸�

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ECP_ItemType ItemType; // ������ Ÿ��

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UTexture2D* ItemIcon; // ������ ������

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 StackCount = 1; //  ������ ���� �߰� (�⺻�� 1)
};