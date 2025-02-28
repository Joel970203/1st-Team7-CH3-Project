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
    AmmoCount = 0;
    MaxAmmo = 0;

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



// ���� �߻� 
void ACP_Guns::Fire()
{
    if (!BarrelInfo) return;

    if (!TriggerInfo || AmmoCount <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("No ammo"));
        return;
    }

    AmmoCount--;

    FVector MuzzleLocation = BarrelMesh->GetSocketLocation(FName("Muzzle"));
    FVector MuzzleDirection = BarrelMesh->GetSocketTransform(FName("Muzzle")).GetRotation().GetRightVector();
    
    if (NiagaraEffect)
    {
        NiagaraEffect->Activate();
        GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ACP_Guns::DeactivateNiagaraEffect, 0.1f, false);
    }

    if (AudioComponent)
    {
        AudioComponent->Play();
    }

    if (BarrelInfo->bIsHitscan)
    {
        FHitResult HitResult;
        FCollisionQueryParams QueryParams;
        QueryParams.AddIgnoredActor(this);
        QueryParams.AddIgnoredActor(GetOwner());
        QueryParams.bTraceComplex = true;

        FVector EndPoint = MuzzleLocation + (MuzzleDirection * 2000.0f);
        bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, MuzzleLocation, EndPoint, ECC_GameTraceChannel1, QueryParams);
    
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
        }

        DrawDebugLine(GetWorld(), MuzzleLocation, EndPoint, FColor::Red, false, 1.0f, 0, 2.0f);
    }
    
    else if (!BarrelInfo->bIsHitscan)
    {
        if (ProjectileClass)
        {
            FRotator ProjectileRotation = MuzzleDirection.Rotation();
            ACP_Projectile* Projectile = GetWorld()->SpawnActor<ACP_Projectile>(ProjectileClass, MuzzleLocation, ProjectileRotation);
            if (Projectile)
            {
                Projectile->SetOwner(this);
                if (Projectile->ProjectileMovement)
                {
                    FVector Velocity = MuzzleDirection * 8000.f;
                    Projectile->ProjectileMovement->Velocity = Velocity;
                    Projectile->ProjectileMovement->Activate();
                }
            }
        }
    }
}


void ACP_Guns::DeactivateNiagaraEffect()
{
    if (NiagaraEffect)
    {
        NiagaraEffect->Deactivate();
    }
}

void ACP_Guns::ApplyDamage(AActor* HitActor)
{
    if (!HitActor) return;

    float TotalDamage = CalculateTotalDamage();

    AActor* OwnerActor = GetOwner();
    AController* OwnerController = nullptr;

    if (OwnerActor)
    {
        APawn* OwnerPawn = Cast<APawn>(OwnerActor);
        if (OwnerPawn)
        {
            OwnerController = OwnerPawn->GetController();
        }
    }

    ACP_Enemy* Enemy = Cast<ACP_Enemy>(HitActor);
    if (Enemy)
    {
       // UE_LOG(Log, TEXT("[ACP_Guns] Enemy hit: %s, Damage: %f"), *Enemy->GetName(), TotalDamage);

        float AppliedDamage = UGameplayStatics::ApplyDamage(
            Enemy,
            TotalDamage,
            OwnerController,
            this,
            UDamageType::StaticClass()
        );

        //UE_LOG(Log, TEXT("[ACP_Guns] Damage applied: %f, Enemy HP: %d"), AppliedDamage, Enemy->CurrentHp);
    }
}


float ACP_Guns::CalculateTotalDamage()
{
    float TotalDamage = 0.0f;
    if (TriggerInfo) TotalDamage += TriggerInfo->Damage;
    if (BodyInfo) TotalDamage += BodyInfo->Damage;
    if (BarrelInfo) TotalDamage += BarrelInfo->Damage;
    return TotalDamage;
}

void ACP_Guns::Reload()
{
    if (!TriggerInfo || !InventoryRef) return;  

    int32 MagazineCapacity = TriggerInfo->MagazineCapacity;

    // ammo �ִ��� üũ
    if (!InventoryRef->HasItem("Ammo"))
    {
        return;
    }

    // MaxAmmo�� ������� Ȯ��
    if (MaxAmmo < MagazineCapacity)
    {
        return;
    }

    //  ������ ����
    AmmoCount = MagazineCapacity;  // źâ ä���
    MaxAmmo -= MagazineCapacity;  // ���� ź�� ����

    // �κ��丮���� Ammo ������ ����
    FCP_ItemInfo AmmoItem;
    AmmoItem.ItemName = "Ammo";
    AmmoItem.ItemType = ECP_ItemType::Ammo;
    InventoryRef->RemoveItem(AmmoItem);

}