#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CP_Guns.generated.h"

UCLASS()
class CYBERPUNK_API ACP_Guns : public AActor
{
    GENERATED_BODY()

public:
    // �ѱ��� �⺻ ����
    ACP_Guns();

protected:
    virtual void BeginPlay() override;

public:
    // �� tick���� ȣ��Ǵ� �Լ�
    virtual void Tick(float DeltaTime) override;

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
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USkeletalMeshComponent* BarrelMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USkeletalMeshComponent* BodyMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USkeletalMeshComponent* TriggerMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USkeletalMeshComponent* ScopeMesh;

    // �跲 ���� �Լ�
    void SetBarrel(USkeletalMeshComponent* SelectedBarrel);
};
