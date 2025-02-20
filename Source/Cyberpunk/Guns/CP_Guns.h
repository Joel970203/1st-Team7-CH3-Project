#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CP_BarrelInfo.h"
#include "CP_BodyInfo.h"
#include "CP_TriggerInfo.h"
#include "CP_Projectile.h"
#include "Kismet/GameplayStatics.h"
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
    USceneComponent* RootScene;  // RootComponent

    // ���� �޽� ������Ʈ
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun Parts")
    USkeletalMeshComponent* BarrelMesh;  // Barrel Mesh

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun Parts")
    USkeletalMeshComponent* BodyMesh;  // Body Mesh

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun Parts")
    USkeletalMeshComponent* TriggerMesh;  // Trigger Mesh

    // ���� ����
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun Parts")
    ACP_BarrelInfo* BarrelInfo;  // BarrelInfo (�跲 ����)

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun Parts")
    ACP_BodyInfo* BodyInfo;  // BodyInfo (��ü ����)

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun Parts")
    ACP_TriggerInfo* TriggerInfo;  // TriggerInfo (Ʈ���� ����)

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

    // ������Ÿ�� Ŭ������ �������Ʈ���� ������ �� �ֵ��� ����
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
    TSubclassOf<ACP_Projectile> ProjectileClass;  // ������Ÿ�� Ŭ����
};
