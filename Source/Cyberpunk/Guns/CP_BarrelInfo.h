#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CP_GunInfo.h"
#include "CP_BarrelInfo.generated.h"

UCLASS()
class CYBERPUNK_API ACP_BarrelInfo : public ACP_GunInfo
{
    GENERATED_BODY()

public:
    ACP_BarrelInfo();
    // �����

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Info")
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

    // �跲 �޽��� ��ȯ�ϴ� �Լ�
    USkeletalMeshComponent* GetBarrelMesh() const;

    // �跲 ���� �ʱ�ȭ
    void InitializeBarrelInfo(const FString& MeshName);
};
