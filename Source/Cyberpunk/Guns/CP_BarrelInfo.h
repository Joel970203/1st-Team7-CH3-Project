#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CP_GunPart.h"  
#include "CP_BarrelInfo.generated.h"

UCLASS()
class CYBERPUNK_API ACP_BarrelInfo : public AActor, public IGunPart
{
    GENERATED_BODY()

public:
    ACP_BarrelInfo();

    // BarrelMesh �ʱ�ȭ
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Barrel Info")
    USkeletalMeshComponent* BarrelMesh;

    // �跲 �̸�
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Barrel Info")
    FString PartName;

    // ��Ʈ��ĵ ����
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Barrel Info")
    bool bIsHitscan;

    // �跲 ������
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Barrel Info")
    float Damage;

    // �跲 ���� �ʱ�ȭ �Լ�
    virtual void Initialize(const FString& MeshName) override;

    // BarrelMesh ��ȯ �Լ�
    virtual USkeletalMeshComponent* GetMesh() const override;

protected:
    UPROPERTY(VisibleAnywhere)
    USceneComponent* RootSceneComponent;
};
