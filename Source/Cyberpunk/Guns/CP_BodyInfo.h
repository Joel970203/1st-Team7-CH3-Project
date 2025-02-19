#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CP_GunInfo.h"
#include "CP_BodyInfo.generated.h"

UCLASS(Blueprintable)
class CYBERPUNK_API ACP_BodyInfo : public ACP_GunInfo
{
    GENERATED_BODY()

public:
    ACP_BodyInfo();

    // BodyMesh �ʱ�ȭ
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Info")
    USkeletalMeshComponent* BodyMesh;

    // �ٵ� �̸�
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Info")
    FString PartName;

    // �ٵ� ������
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Info")
    float Damage;

    // �̵� �ӵ�
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Info")
    float MovementSpeed;

    // Body ���� �ʱ�ȭ �Լ�
    void InitializeBodyInfo(const FString& MeshName);

    // BodyMesh ��ȯ �Լ�
    USkeletalMeshComponent* GetBodyMesh() const;

protected:
    // RootComponent�� SceneComponent�� ����
    UPROPERTY(VisibleAnywhere)
    USceneComponent* RootSceneComponent;
};

