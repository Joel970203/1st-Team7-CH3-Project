#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CP_BarrelInfo.h"
#include "CP_BodyInfo.h"
#include "CP_TriggerInfo.h"
#include "CP_Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "NiagaraComponent.h"  
#include "CP_Guns.generated.h"

UCLASS()
class CYBERPUNK_API ACP_Guns : public AActor
{
    GENERATED_BODY()

public:
    ACP_Guns();

protected:
    // virtual void BeginPlay() override;

public:
    // ��Ʈ �� ������Ʈ
    UPROPERTY(VisibleAnywhere)
    USceneComponent* RootScene;

    // ���� �޽� ������Ʈ
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun Parts")
    USkeletalMeshComponent* BarrelMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun Parts")
    USkeletalMeshComponent* BodyMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun Parts")
    USkeletalMeshComponent* TriggerMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun Parts")
    ACP_BarrelInfo* BarrelInfo;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun Parts")
    ACP_BodyInfo* BodyInfo;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun Parts")
    ACP_TriggerInfo* TriggerInfo;


    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sound")
    UAudioComponent* AudioComponent;

    // �߻� Ÿ�̸� ����
    float FireTimer;

    // �߻� ���� ����
    UPROPERTY(EditAnywhere, Category = "Gun Properties")
    float FireRate;

    // �߻� �Լ�
    void Fire();

    // �߻��� �� ����ϴ� �Լ�
    void FireProjectile();

    // �⺻ ���� ���� �Լ�
    void SetGunParts(ACP_BarrelInfo* Barrel, ACP_BodyInfo* Body, ACP_TriggerInfo* Trigger);

    // Ÿ�̸Ӹ� �����ϴ� �Լ� (�� ������ ȣ��)
    virtual void Tick(float DeltaTime) override;

    // �⺻ ���� �ε� �Լ�
    void LoadGunParts();

    void DeactivateNiagaraEffect();

    // �߻��� ������Ÿ�� Ŭ����
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
    TSubclassOf<ACP_Projectile> ProjectileClass; 

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Niagara")
    UNiagaraComponent* NiagaraEffect;

    FTimerHandle TimerHandle;
};
