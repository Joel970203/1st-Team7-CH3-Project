#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CP_GunInfo.h"
#include "CP_TriggerInfo.generated.h"

UCLASS()
class CYBERPUNK_API ACP_TriggerInfo : public ACP_GunInfo
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ACP_TriggerInfo();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Info")
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
    void InitializeTriggerInfo(const FString& MeshName);

    // Ʈ���� �޽��� ��ȯ�ϴ� �Լ�
    USkeletalMeshComponent* GetTriggerMesh() const;
};
