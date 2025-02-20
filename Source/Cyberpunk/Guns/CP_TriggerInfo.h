#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunPart.h"
#include "CP_TriggerInfo.generated.h"

UCLASS(Blueprintable)
class CYBERPUNK_API ACP_TriggerInfo : public AActor, public IGunPart
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ACP_TriggerInfo();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger Info")
    USkeletalMeshComponent* TriggerMesh;

    // Ʈ���� �̸�
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger Info")
    FString PartName;

    // Ʈ���� ������
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger Info")
    float Damage;

    // źâ ũ��
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger Info")
    int32 MagazineCapacity;

    // Ʈ���� ���� �ʱ�ȭ �Լ�
    virtual void Initialize(const FString& MeshName) override;

    // Ʈ���� �޽��� ��ȯ�ϴ� �Լ�
    virtual USkeletalMeshComponent* GetMesh() const override;

protected:
    // RootComponent�� SceneComponent�� ����
    UPROPERTY(VisibleAnywhere)
    USceneComponent* RootSceneComponent;
};
