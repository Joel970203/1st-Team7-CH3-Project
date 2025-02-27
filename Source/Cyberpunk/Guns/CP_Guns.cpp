#include "CP_Guns.h"

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

    // ���� ���� 
    BarrelInfo = CreateDefaultSubobject<ACP_BarrelInfo>(TEXT("BarrelInfo"));
    BodyInfo = CreateDefaultSubobject<ACP_BodyInfo>(TEXT("BodyInfo"));
    TriggerInfo = CreateDefaultSubobject<ACP_TriggerInfo>(TEXT("TriggerInfo"));

    // ���̾ư��� ����Ʈ 
    NiagaraEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraEffect"));
    NiagaraEffect->SetupAttachment(RootScene);

    // ����� ������Ʈ
    AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
    AudioComponent->SetupAttachment(RootScene);

    // Tactical Light 
    TacticalLightComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("TacticalLight"));
    TacticalLightComponent->SetupAttachment(BodyMesh, FName("Light"));

    static ConstructorHelpers::FClassFinder<AActor> HitEffectBP(TEXT("Blueprint'/Game/FXVarietyPack/Blueprints/BP_ky_hit2.BP_ky_hit2_C'"));
    if (HitEffectBP.Succeeded())
    {
        HitEffectBPClass = HitEffectBP.Class;
    }

    // �߻� Ÿ�̸�
    FireTimer = 0.0f;

    //�߻��� ������Ÿ�� 
    static ConstructorHelpers::FClassFinder<ACP_Projectile> ProjectileBPClass(TEXT("Blueprint'/Game/Gun_BluePrint/BP_Projectile.BP_Projectile_C'"));
    if (ProjectileBPClass.Succeeded())
    {
        ProjectileClass = ProjectileBPClass.Class;
    }

    // �߻� ���� 
    static ConstructorHelpers::FObjectFinder<USoundCue> FireSoundCueAsset(TEXT("SoundCue'/Game/Gun_BluePrint/MuzzleFlash/Demo/FPWeapon/Cue/FirstPersonTemplateWeaponFire02_Cue.FirstPersonTemplateWeaponFire02_Cue'"));
    if (FireSoundCueAsset.Succeeded() && AudioComponent)
    {
        AudioComponent->SetSound(FireSoundCueAsset.Object);
    }

    //�⺻ ���� �ε� 
    LoadGunParts();
}


void ACP_Guns::EquipPart(const FString& PartName, EGunPartType PartType)
{
    if (PartType == EGunPartType::Barrel)
    {
        if (BarrelInfo)
        {
            BarrelInfo->Destroy();  // ���� �跲 ���� ����
        }

        BarrelInfo = GetWorld()->SpawnActor<ACP_BarrelInfo>(ACP_BarrelInfo::StaticClass());
        if (BarrelInfo)
        {
            BarrelInfo->Initialize(PartName);
            BarrelMesh->SetSkeletalMesh(BarrelInfo->GetMesh()->SkeletalMesh);

            UE_LOG(LogTemp, Log, TEXT("[ACP_Guns] Barrel changed to: %s"), *PartName);
        }
    }
    else if (PartType == EGunPartType::Body)
    {
        if (BodyInfo)
        {
            BodyInfo->Destroy();  // ���� �ٵ� ���� ����
        }

        BodyInfo = GetWorld()->SpawnActor<ACP_BodyInfo>(ACP_BodyInfo::StaticClass());
        if (BodyInfo)
        {
            BodyInfo->Initialize(PartName);
            BodyMesh->SetSkeletalMesh(BodyInfo->GetMesh()->SkeletalMesh);

            UE_LOG(LogTemp, Log, TEXT("[ACP_Guns] Body changed to: %s"), *PartName);
        }
    }
    else if (PartType == EGunPartType::Trigger)
    {
        if (TriggerInfo)
        {
            TriggerInfo->Destroy();  // ���� Ʈ���� ���� ����
        }

        TriggerInfo = GetWorld()->SpawnActor<ACP_TriggerInfo>(ACP_TriggerInfo::StaticClass());
        if (TriggerInfo)
        {
            TriggerInfo->Initialize(PartName);
            TriggerMesh->SetSkeletalMesh(TriggerInfo->GetMesh()->SkeletalMesh);

            UE_LOG(LogTemp, Log, TEXT("[ACP_Guns] Trigger changed to: %s"), *PartName);
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("[ACP_Guns] Invalid part type: %s"), *PartName);
    }
}


//�⺻ ���� �ε� 
void ACP_Guns::LoadGunParts()
{
    USkeletalMesh* BarrelSkeletalMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/DUWepCustSys/Meshes/SK_BarrelBeam.SK_BarrelBeam")));
    if (BarrelSkeletalMesh)
    {
        BarrelMesh->SetSkeletalMesh(BarrelSkeletalMesh);
        if (BarrelInfo)
        {
            BarrelInfo->Initialize("SK_BarrelBeam");
        }

        UNiagaraSystem* NiagaraAsset = Cast<UNiagaraSystem>(StaticLoadObject(UNiagaraSystem::StaticClass(), nullptr, TEXT("NiagaraSystem'/Game/Gun_BluePrint/MuzzleFlash/MuzzleFlash/Niagara/NS_MuzzleFlash.NS_MuzzleFlash'")));
        if (NiagaraAsset)
        {
            NiagaraEffect->SetAsset(NiagaraAsset);
            NiagaraEffect->SetupAttachment(BarrelMesh, FName("Muzzle"));
        }
    }

    USkeletalMesh* BodySkeletalMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/DUWepCustSys/Meshes/SK_BodyFire.SK_BodyFire")));
    if (BodySkeletalMesh)
    {
        BodyMesh->SetSkeletalMesh(BodySkeletalMesh);
    }

    USkeletalMesh* TriggerSkeletalMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/DUWepCustSys/Meshes/SK_TriggerSingle.SK_TriggerSingle")));
    if (TriggerSkeletalMesh)
    {
        TriggerMesh->SetSkeletalMesh(TriggerSkeletalMesh);
    }
}

// ƽ �Լ� 
void ACP_Guns::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    NiagaraEffect->Deactivate();

    FireTimer += DeltaTime;
    if (FireTimer >= 1.0f)
    {
        Fire();
        FireTimer = 0.0f;
    }
}

// ���� �߻� 
void ACP_Guns::Fire()
{

    if (BarrelInfo)
    {
        if (BarrelInfo->bIsHitscan)
        {
            FireHitscan();
        }
        else if(!BarrelInfo->bIsHitscan)
        {
            FireProjectile();
        }
    }
}

// ������Ÿ�� �߻� 
void ACP_Guns::FireProjectile()
{
    FVector MuzzleLocation = BarrelMesh->GetSocketLocation(FName("Muzzle"));

    // ������ Right ���͸� �����ͼ� �߻� ���� ��� 
    FVector RightVector = BarrelMesh->GetSocketTransform(FName("Muzzle")).GetRotation().GetRightVector();
    FVector LaunchDirection = RightVector;
    FVector Velocity = LaunchDirection * 8000.f;

    // ���̾ư��� ����Ʈ Ȱ��ȭ 
    if (NiagaraEffect)
    {
        NiagaraEffect->Activate();

        // 0.1�� �Ŀ� ���̾ư��� ����Ʈ ��Ȱ��ȭ 
        GetWorld()->GetTimerManager().SetTimer(
            TimerHandle,
            this,
            &ACP_Guns::DeactivateNiagaraEffect,
            0.1f,
            false
        );
    }

    if (AudioComponent)
    {
        AudioComponent->Play();
    }

    if (ProjectileClass)
    {
        FRotator ProjectileRotation = LaunchDirection.Rotation();
        ACP_Projectile* Projectile = GetWorld()->SpawnActor<ACP_Projectile>(ProjectileClass, MuzzleLocation, ProjectileRotation);
        if (Projectile)
        {
            Projectile->SetOwner(this);
            if (Projectile->ProjectileMovement)
            {
                Projectile->ProjectileMovement->Velocity = Velocity;
                Projectile->ProjectileMovement->Activate();
            }
        }
    }
}

// ��Ʈ��ĵ ��� �߻�
void ACP_Guns::FireHitscan()
{
    FVector MuzzleLocation = BarrelMesh->GetSocketLocation(FName("Muzzle"));
    FVector ForwardVector = BarrelMesh->GetSocketTransform(FName("Muzzle")).GetRotation().GetRightVector();
    FVector EndPoint = MuzzleLocation + (ForwardVector * 1000.0f);

    FHitResult HitResult;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(this);
    QueryParams.AddIgnoredActor(GetOwner());
    QueryParams.bTraceComplex = true;

    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, MuzzleLocation, EndPoint, ECC_Pawn, QueryParams);
    if (bHit)
    {
        EndPoint = HitResult.ImpactPoint;

        if (HitEffectBPClass)
        {
            AActor* HitEffect = GetWorld()->SpawnActor<AActor>(HitEffectBPClass, EndPoint, FRotator::ZeroRotator);
            if (HitEffect)
            {
                HitEffect->SetActorScale3D(FVector(0.1f, 0.1f, 0.1f));
            }
        }

        if (NiagaraEffect)
        {
            NiagaraEffect->Activate();

            GetWorld()->GetTimerManager().SetTimer(
                TimerHandle,
                this,
                &ACP_Guns::DeactivateNiagaraEffect,
                0.1f,
                false
            );
        }

        if (AudioComponent)
        {
            AudioComponent->Play();
        }
    }

    DrawDebugLine(GetWorld(), MuzzleLocation, EndPoint, FColor::Red, false, 1.0f, 0, 2.0f);
}





void ACP_Guns::DeactivateNiagaraEffect()
{
    if (NiagaraEffect)
    {
        NiagaraEffect->Deactivate();
    }
}
