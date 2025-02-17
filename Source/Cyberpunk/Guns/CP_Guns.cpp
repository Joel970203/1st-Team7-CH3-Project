#include "CP_Guns.h"

ACP_Guns::ACP_Guns()
{
    PrimaryActorTick.bCanEverTick = true;
    AmmoCount = 30;
    MaxAmmo = 30;
    bIsReloading = false;
    ReloadTime = 2.0f;

    // Root �� ������Ʈ ����
    RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
    RootComponent = RootScene;

    // �ѱ� ��ǰ�� (���̷�Ż �޽�) 
    BarrelMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BarrelMesh"));
    BodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BodyMesh"));
    TriggerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TriggerMesh"));
    ScopeMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ScopeMesh"));

    // �ѱ� ��ǰ���� Root �� ������Ʈ�� ����
    BarrelMesh->SetupAttachment(RootScene, TEXT("BarrelSocket"));
    BodyMesh->SetupAttachment(RootScene, TEXT("BodySocket"));
    TriggerMesh->SetupAttachment(RootScene, TEXT("TriggerSocket"));
    ScopeMesh->SetupAttachment(RootScene, TEXT("ScopeSocket"));
}

void ACP_Guns::BeginPlay()
{
    Super::BeginPlay();

    if (BarrelMesh)
    {
        BarrelMesh->AttachToComponent(RootScene, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("BarrelSocket"));
    }
    BodyMesh->AttachToComponent(RootScene, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("BodySocket"));
    TriggerMesh->AttachToComponent(RootScene, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("TriggerSocket"));
    ScopeMesh->AttachToComponent(RootScene, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("ScopeSocket"));


    if (BarrelMesh)
    {
        SetBarrel(BarrelMesh);
    }
}

void ACP_Guns::SetBarrel(USkeletalMeshComponent* SelectedBarrel)
{
    BarrelMesh = SelectedBarrel;

    if (BarrelMesh)
    {
        // SkeletalMeshAsset �̸��� Ȯ���Ͽ� �±� �߰�
        FString MeshName = BarrelMesh->GetSkeletalMeshAsset()->GetName();
        UE_LOG(LogTemp, Log, TEXT("Selected Barrel: %s"), *MeshName);

        if (MeshName == "SK_BarrelBeam" || MeshName == "SK_BarrelBeamScatter")
        {
            // ��Ʈ��ĵ ���
            BarrelMesh->ComponentTags.Add(FName("Hitscan"));
            UE_LOG(LogTemp, Log, TEXT("Fire Mode: Hitscan"));
        }
        else if (MeshName == "SK_BarrelBulletScatter" || MeshName == "SK_BarrelBullet")
        {
            // ������Ÿ�� ���
            BarrelMesh->ComponentTags.Add(FName("Projectile"));
            UE_LOG(LogTemp, Log, TEXT("Fire Mode: Projectile"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("BarrelMesh is null!"));
    }
}


void ACP_Guns::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // �� ƽ���� Fire() �Լ� ȣ�� (�׽�Ʈ��)
    if (AmmoCount > 0)
    {
        Fire();
    }
}


void ACP_Guns::Fire()
{
    if (AmmoCount > 0)
    {
        // �߻� ȿ���� ó�� (��Ʈ��ĵ �Ǵ� ������Ÿ�� ó��)
        if (BarrelMesh->ComponentHasTag(FName("Hitscan")))
        {
            UE_LOG(LogTemp, Log, TEXT("Hit scan Fire! Ammo left: %d"), AmmoCount);
            AmmoCount--;
            // ��Ʈ��ĵ �߻� ó�� ����
            

        }
        // ������Ÿ�� �߻� ���
        else if (BarrelMesh->ComponentHasTag(FName("Projectile")))
        {
            UE_LOG(LogTemp, Log, TEXT("Projectile Fire! Ammo left: %d"), AmmoCount);
            AmmoCount--;
            // ������Ÿ�� �߻� ó�� ����
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Out of ammo!"));
        Reload();
    }
}


void ACP_Guns::Reload()
{
    // �⺻���� ������ ���
}

void ACP_Guns::AttachAttachment(const FString& AttachmentName)
{
    // �⺻���� ������ ���� ���
}
