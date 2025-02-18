#include "CP_BodyInfo.h"

ACP_BodyInfo::ACP_BodyInfo()
{
    // �⺻�� ���� (�ʿ�� �ʱⰪ ����)
    PartName = "Unknown";
    Damage = 0.0f;
    MovementSpeed = 1.0f;

    // BodyMesh �ʱ�ȭ (�ʿ��)
    BodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BodyMesh"));
}

void ACP_BodyInfo::InitializeBodyInfo(const FString& MeshName)
{
    if (MeshName == "SK_BodyTesla")
    {
        // ������ 100, �̵��ӵ� 1.0��
        PartName = "SK_BodyTesla";
        Damage = 100.0f;
        MovementSpeed = 1.0f;
    }
    else if (MeshName == "SK_BodyNormal")
    {
        // ������ 130, �̵��ӵ� 0.9��
        PartName = "SK_BodyNormal";
        Damage = 130.0f;
        MovementSpeed = 0.9f;
    }
    else if (MeshName == "SK_BodyFire")
    {
        // ������ 200, �̵��ӵ� 0.5��
        PartName = "SK_BodyFire";
        Damage = 200.0f;
        MovementSpeed = 0.5f;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Unknown Body: %s"), *MeshName);
    }
}


USkeletalMeshComponent* ACP_BodyInfo::GetBodyMesh() const
{
    return BodyMesh;
}

