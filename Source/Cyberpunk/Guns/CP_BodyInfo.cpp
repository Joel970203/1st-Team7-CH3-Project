#include "CP_BodyInfo.h"
#include "Engine/Texture2D.h"

ACP_BodyInfo::ACP_BodyInfo()
{
    RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
    RootComponent = RootSceneComponent;

    BodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BodyMesh"));
    BodyMesh->SetupAttachment(RootSceneComponent);

    // �⺻�� ����
    IconTexture = nullptr;
    IconTexturePath = TEXT(""); // �⺻ ��� �ʱ�ȭ
}

void ACP_BodyInfo::Initialize(const FString& MeshName)
{
    USkeletalMesh* LoadedMesh = nullptr;

    if (MeshName == "SK_BodyTesla")
    {
        PartName = "SK_BodyTesla";
        Damage = 100.0f;
        MovementSpeed = 1.0f;
        GearCost = 5;
        LoadedMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/DUWepCustSys/Meshes/SK_BodyTesla.SK_BodyTesla")));
        IconTexturePath = TEXT("/Game/Gun_BluePrint/RenderTargets/SK_BodyTesla.SK_BodyTesla");
    }
    else if (MeshName == "SK_BodyNormal")
    {
        PartName = "SK_BodyNormal";
        Damage = 130.0f;
        MovementSpeed = 0.9f;
        GearCost = 4;
        LoadedMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/DUWepCustSys/Meshes/SK_BodyNormal.SK_BodyNormal")));
        IconTexturePath = TEXT("/Game/Gun_BluePrint/RenderTargets/SK_BodyNormal.SK_BodyNormal");
    }
    else if (MeshName == "SK_BodyFire")
    {
        PartName = "SK_BodyFire";
        Damage = 200.0f;
        MovementSpeed = 0.5f;
        GearCost = 5;
        LoadedMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/DUWepCustSys/Meshes/SK_BodyFire.SK_BodyFire")));
        IconTexturePath = TEXT("/Game/Gun_BluePrint/RenderTargets/SK_BodyFire.SK_BodyFire");
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Unknown Body: %s"), *MeshName);
    }

    if (LoadedMesh)
    {
        BodyMesh->SetSkeletalMesh(LoadedMesh);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load Mesh: %s"), *MeshName);
    }

    // ������ �ε�
    LoadIconTexture();
}

/** ������ �ε� �Լ� */
void ACP_BodyInfo::LoadIconTexture()
{
    if (!IconTexturePath.IsEmpty())
    {
        IconTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *IconTexturePath));
        if (!IconTexture)
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to load IconTexture: %s"), *IconTexturePath);
        }
    }
}

USkeletalMeshComponent* ACP_BodyInfo::GetMesh() const
{
    return BodyMesh;
}
