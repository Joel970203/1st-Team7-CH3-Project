#include "CP_Projectile.h"



ACP_Projectile::ACP_Projectile()
{
    PrimaryActorTick.bCanEverTick = true;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
    CollisionComponent->InitSphereRadius(10.0f);
    CollisionComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));  // �浹 ����
    RootComponent = CollisionComponent;

    NiagaraEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraEffect"));
    NiagaraEffect->SetupAttachment(RootComponent);

    static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraSystem(TEXT("/Game/Gun_BluePrint/NS_bullet.NS_bullet"));
    if (NiagaraSystem.Succeeded())
    {
        NiagaraEffect->SetAsset(NiagaraSystem.Object);
    }

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->InitialSpeed = 2000.f;
    ProjectileMovement->MaxSpeed = 2000.f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->bShouldBounce = false;
    ProjectileMovement->ProjectileGravityScale = 0.0f;

    CollisionComponent->OnComponentHit.AddDynamic(this, &ACP_Projectile::OnHit);
}

void ACP_Projectile::BeginPlay()
{
    Super::BeginPlay();

    // 2�� �� �ڵ� ����
    SetLifeSpan(2.0f);

    // ���̾ư��� ����Ʈ ����
    if (NiagaraEffect)
    {
        NiagaraEffect->Activate(true);
    }
}

// �߻� �Լ�
void ACP_Projectile::LaunchProjectile(const FVector& LaunchDirection)
{
    if (ProjectileMovement)
    {
        // �߻� ���� ����
        FVector LaunchVelocity = LaunchDirection * 2000.f;
        ProjectileMovement->Velocity = LaunchVelocity;
        ProjectileMovement->Activate();

        UE_LOG(LogTemp, Warning, TEXT("fire: %s"), *LaunchDirection.ToString());
    }
}




// �浹 �� ȣ��� �Լ�
void ACP_Projectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor && OtherActor != this)
    {

        // ���⼭ �浹 ȿ�� �߰� ����
        // 
        Destroy();  // �浹 �� ����
    }
}
