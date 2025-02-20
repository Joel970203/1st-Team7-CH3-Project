#include "CP_Guns.h"
#include "CP_BarrelInfo.h"
#include "CP_BodyInfo.h"
#include "CP_TriggerInfo.h"
#include "Kismet/GameplayStatics.h"

ACP_Guns::ACP_Guns()
{
    PrimaryActorTick.bCanEverTick = true;

    RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
    RootComponent = RootScene;

    BarrelMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BarrelMesh"));
    BarrelMesh->SetupAttachment(RootScene);

    BodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BodyMesh"));
    BodyMesh->SetupAttachment(RootScene);

    TriggerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TriggerMesh"));
    TriggerMesh->SetupAttachment(RootScene);

    BarrelInfo = CreateDefaultSubobject<ACP_BarrelInfo>(TEXT("BarrelInfo"));
    BodyInfo = CreateDefaultSubobject<ACP_BodyInfo>(TEXT("BodyInfo"));
    TriggerInfo = CreateDefaultSubobject<ACP_TriggerInfo>(TEXT("TriggerInfo"));

    FireTimer = 0.0f;

    // �⺻ ���� �ε� (�跲, �ٵ�, Ʈ����)
    LoadGunParts();
}

void ACP_Guns::LoadGunParts()
{
    // �ѱ� �⺻ ������ ����

    USkeletalMesh* BarrelSkeletalMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/DUWepCustSys/Meshes/SK_BarrelBulletScatter.SK_BarrelBulletScatter")));
    if (BarrelSkeletalMesh)
    {
        BarrelMesh->SetSkeletalMesh(BarrelSkeletalMesh);

        // BarrelInfo �ʱ�ȭ
        if (BarrelInfo)
        {
            BarrelInfo->Initialize("SK_BarrelBulletScatter");  
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("BarrelInfo is null"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load Barrel Mesh"));
    }

    USkeletalMesh* BodySkeletalMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/DUWepCustSys/Meshes/SK_BodyFire.SK_BodyFire")));
    if (BodySkeletalMesh)
    {
        BodyMesh->SetSkeletalMesh(BodySkeletalMesh);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load Body Mesh"));
    }

    USkeletalMesh* TriggerSkeletalMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/DUWepCustSys/Meshes/SK_TriggerSingle.SK_TriggerSingle")));
    if (TriggerSkeletalMesh)
    {
        TriggerMesh->SetSkeletalMesh(TriggerSkeletalMesh);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load Trigger Mesh"));
    }
}

void ACP_Guns::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // �߻� ���� ���� (�ʴ� 1ȸ �߻�) �̰� �׽�Ʈ���Դϴ�.
    FireTimer += DeltaTime;
    if (FireTimer >= 1.0f)  // 1�ʸ��� �߻�
    {
        Fire();
        FireTimer = 0.0f;  // Ÿ�̸� ����
    }
}

void ACP_Guns::Fire()
{
    if (BarrelInfo)
    {
        if (BarrelInfo->bIsHitscan)
        {
            // FireHitscan(); 
        }
        else
        {
            FireProjectile();
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("ACP_Guns::Fire - BarrelInfo not found!"));
    }
}

void ACP_Guns::FireProjectile()
{
    FVector MuzzleLocation = BarrelMesh->GetSocketLocation(FName("Muzzle"));
    FRotator MuzzleRotation = BarrelMesh->GetSocketRotation(FName("Muzzle"));

    // MuzzleRotation�� Pitch�� 0���� �����Ͽ� �������� ���ϰ� ��
    MuzzleRotation.Pitch = 0.0f;

    // �߻� ���� ��� (���� �������� ��������)
    FVector LaunchDirection = MuzzleRotation.Vector();  // �߻� ����
    FVector Velocity = LaunchDirection * 8000.f;  // �߻� �ӵ� ����

    UE_LOG(LogTemp, Log, TEXT("MuzzleLocation: %s, MuzzleRotation: %s, LaunchDirection: %s"), *MuzzleLocation.ToString(), *MuzzleRotation.ToString(), *LaunchDirection.ToString());

    if (ProjectileClass)
    {
        ACP_Projectile* Projectile = GetWorld()->SpawnActor<ACP_Projectile>(ProjectileClass, MuzzleLocation, MuzzleRotation);
        if (Projectile)
        {
            // �߻��� �ѱ��� ������ Projectile�� ����
            Projectile->SetOwner(this);

            // ���� �ùķ��̼��� ��Ȱ��ȭ // �̰� üũ 
            if (Projectile->ProjectileMesh)
            {
                Projectile->ProjectileMesh->SetSimulatePhysics(false);
            }

            // �������� �ʱ� �ӵ� ���� (Velocity�� �ʱ� �ӵ� ����)
            if (Projectile->ProjectileMovement)
            {
                Projectile->ProjectileMovement->Velocity = Velocity;  // �������� �ӵ� ����
                Projectile->ProjectileMovement->Activate();  // Activate ȣ��
            }

            UE_LOG(LogTemp, Log, TEXT("Projectile fired successfully!"));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to spawn Projectile"));
        }
    }
}




