#include "CP_BarrelInfo.h"

ACP_BarrelInfo::ACP_BarrelInfo()
{
    // �⺻�� ���� (�ʿ�� �ʱⰪ ����)
    PartName = "Unknown";
    bIsHitscan = false;
    Damage = 0.0f;

    // BarrelMesh �ʱ�ȭ (�ʿ��)
    BarrelMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BarrelMesh"));
}

void ACP_BarrelInfo::InitializeBarrelInfo(const FString& MeshName)
{
    if (MeshName == "SK_BarrelBeam")
    {
        // ��Ʈ��ĵ, ������ 50
        PartName = "SK_BarrelBeam";
        bIsHitscan = true;
        Damage = 50.0f;
    }
    else if (MeshName == "SK_BarrelBeamScatter")
    {
        // ��Ʈ��ĵ, ������ 70
        PartName = "SK_BarrelBeamScatter";
        bIsHitscan = true;
        Damage = 70.0f;
    }
    else if (MeshName == "SK_BarrelBulletScatter")
    {
        // ������Ÿ��, ������ 100
        PartName = "SK_BarrelBulletScatter";
        bIsHitscan = false;
        Damage = 100.0f;
    }
    else if (MeshName == "SK_BarrelRocketScatter")
    {
        // ������Ÿ��, ������ 150
        PartName = "SK_BarrelRocketScatter";
        bIsHitscan = false;
        Damage = 150.0f;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Unknown Barrel: %s"), *MeshName);
    }
}


USkeletalMeshComponent* ACP_BarrelInfo::GetBarrelMesh() const
{
    return BarrelMesh;
}
