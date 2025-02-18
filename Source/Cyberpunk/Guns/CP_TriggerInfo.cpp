#include "CP_TriggerInfo.h"

ACP_TriggerInfo::ACP_TriggerInfo()
{
    // �⺻�� ���� (�ʿ�� �ʱⰪ ����)
    PartName = "Unknown";
    Damage = 0.0f;
    MagazineCapacity = 0;
}

void ACP_TriggerInfo::InitializeTriggerInfo(const FString& MeshName)
{
    if (MeshName == "SK_TriggerAuto")
    {
        // ������ 10, źâ ũ�� 70
        PartName = "SK_TriggerAuto";
        Damage = 10.0f;
        MagazineCapacity = 70;
    }
    else if (MeshName == "SK_TriggerBurst")
    {
        // ������ 20, źâ ũ�� 60
        PartName = "SK_TriggerBurst";
        Damage = 20.0f;
        MagazineCapacity = 60;
    }
    else if (MeshName == "SK_StockStandard")
    {
        // ������ 25, źâ ũ�� 50
        PartName = "SK_StockStandard";
        Damage = 25.0f;
        MagazineCapacity = 50;
    }
    else if (MeshName == "SK_StockHeavy")
    {
        // ������ 30, źâ ũ�� 30
        PartName = "SK_StockHeavy";
        Damage = 30.0f;
        MagazineCapacity = 30;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Unknown Trigger: %s"), *MeshName);
    }

}
USkeletalMeshComponent* ACP_TriggerInfo::GetTriggerMesh() const
{
    return TriggerMesh;
}