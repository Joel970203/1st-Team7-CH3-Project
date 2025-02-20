#include "CP_Projectile.h"
#include "UObject/ConstructorHelpers.h"  // StaticLoadObject ����� ���� ��� �߰�

ACP_Projectile::ACP_Projectile()
{
    PrimaryActorTick.bCanEverTick = true;

    // Root Scene Component �߰�
    RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
    RootComponent = RootScene;

    // Projectile Mesh ����
    ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
    ProjectileMesh->SetupAttachment(RootComponent);

    // Projectile Movement ����
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->bAutoActivate = false;  // �ʱ⿡�� ��Ȱ��ȭ

    // �Ѿ� �޽� ��η� �ε�
    static ConstructorHelpers::FObjectFinder<UStaticMesh> BulletMesh(TEXT("/Game/Gun_BluePrint/Bullet/9mm.9mm"));
    if (BulletMesh.Succeeded())
    {
        ProjectileMesh->SetStaticMesh(BulletMesh.Object);  // �ε��� �޽��� ����
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load Bullet Mesh"));
    }
}

void ACP_Projectile::BeginPlay()
{
    Super::BeginPlay();

    // �Ѿ� �޽� ������ ����
    if (ProjectileMesh)
    {
        ProjectileMesh->SetWorldScale3D(FVector(0.025f, 0.025f, 0.025f));
        ProjectileMesh->SetSimulatePhysics(false);  // ���� �ùķ��̼� ��Ȱ��ȭ
    }

    // ProjectileMovement ����
    if (ProjectileMovement)
    {
        ProjectileMovement->InitialSpeed = 30000.f;
        ProjectileMovement->MaxSpeed = 30000.f;
        ProjectileMovement->bRotationFollowsVelocity = true;
        ProjectileMovement->bShouldBounce = true;
    }
}

// �߻� �Լ� �߰�
void ACP_Projectile::LaunchProjectile(const FVector& LaunchDirection)
{
    if (ProjectileMovement)
    {
        // �߻� ���� ����
        FVector LaunchVelocity = LaunchDirection * ProjectileMovement->InitialSpeed;
        ProjectileMovement->Velocity = LaunchVelocity;

        // ProjectileMovement Ȱ��ȭ
        ProjectileMovement->Activate();
    }
}
