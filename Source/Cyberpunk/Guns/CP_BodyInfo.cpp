#include "CP_BodyInfo.h"

ACP_BodyInfo::ACP_BodyInfo()
{
    // �⺻ RootComponent�� SceneComponent�� ����
    RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
    RootComponent = RootSceneComponent;  // RootComponent ����

    // BodyMesh �ʱ�ȭ
    BodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BodyMesh"));
    BodyMesh->SetupAttachment(RootSceneComponent);  // BodyMesh�� RootComponent�� �ڽ�
}

void ACP_BodyInfo::InitializeBodyInfo(const FString& MeshName)
{
    if (MeshName == "SK_BodyTesla")
    {
        PartName = "SK_BodyTesla";
        Damage = 100.0f;
        MovementSpeed = 1.0f;

        // StaticLoadObject�� �޽� �ε�
        USkeletalMesh* LoadedMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/DUWepCustSys/Meshes/SK_BodyTesla.SK_BodyTesla")));
        if (LoadedMesh)
        {
            BodyMesh->SetSkeletalMesh(LoadedMesh);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to load Mesh: %s"), *MeshName);
        }
    }
    else if (MeshName == "SK_BodyNormal")
    {
        PartName = "SK_BodyNormal";
        Damage = 130.0f;
        MovementSpeed = 0.9f;

        // StaticLoadObject�� �޽� �ε�
        USkeletalMesh* LoadedMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/DUWepCustSys/Meshes/SK_BodyNormal.SK_BodyNormal")));
        if (LoadedMesh)
        {
            BodyMesh->SetSkeletalMesh(LoadedMesh);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to load Mesh: %s"), *MeshName);
        }
    }
    else if (MeshName == "SK_BodyFire")
    {
        PartName = "SK_BodyFire";
        Damage = 200.0f;
        MovementSpeed = 0.5f;

        // StaticLoadObject�� �޽� �ε�
        USkeletalMesh* LoadedMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/DUWepCustSys/Meshes/SK_BodyFire.SK_BodyFire")));
        if (LoadedMesh)
        {
            BodyMesh->SetSkeletalMesh(LoadedMesh);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to load Mesh: %s"), *MeshName);
        }
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
