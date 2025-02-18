#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CP_GunInfo.h"
#include "CP_BarrelInfo.h"
#include "CP_BodyInfo.h"
#include "CP_TriggerInfo.h"
#include "CP_Guns.generated.h"

UCLASS()
class CYBERPUNK_API ACP_Guns : public AActor
{
    GENERATED_BODY()

public:
    // �ѱ��� �⺻ ����
    ACP_Guns();

protected:

public:


    // �ѱ��� �߻� ���
    virtual void Fire();

    // �ѱ��� ������ ���
    virtual void Reload();

    // �ѱ��� ���� ź�� ��
    int32 AmmoCount;

    // �ִ� ź�� ��
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    int32 MaxAmmo;

    // ������ �� ����
    bool bIsReloading;

    // ������ �ð�
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    float ReloadTime;

    // Root �� ������Ʈ
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USceneComponent* RootScene;

    // �ѱ� ��ǰ�� (���̷�Ż �޽�)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun Parts")
    USkeletalMeshComponent* BarrelMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun Parts")
    USkeletalMeshComponent* BodyMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun Parts")
    USkeletalMeshComponent* TriggerMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun Parts")
    USkeletalMeshComponent* ScopeMesh;

    // �跲 ���� �Լ�
    void SetBarrel(USkeletalMeshComponent* SelectedBarrel);

    // �ٵ� ���� �Լ�
    void SetBody(USkeletalMeshComponent* SelectedBody);

    // Ʈ���� ���� �Լ�
    void SetTrigger(USkeletalMeshComponent* SelectedTrigger);

    // ������ ���� �Լ�
    void SetScope(USkeletalMeshComponent* SelectedScope);

    // �ѱ� ��ǰ���� �����ϴ� �Լ�
    void SetGunParts(ACP_BarrelInfo* Barrel, ACP_BodyInfo* Body, ACP_TriggerInfo* Trigger);
};
