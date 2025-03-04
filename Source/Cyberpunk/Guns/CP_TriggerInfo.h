#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CP_GunPart.h"
#include "Engine/Texture2D.h"
#include "CP_TriggerInfo.generated.h"

UCLASS(Blueprintable)
class CYBERPUNK_API ACP_TriggerInfo : public AActor, public IGunPart
{
    GENERATED_BODY()

public:
    ACP_TriggerInfo();

    /** Ʈ���� �޽� */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger Info")
    USkeletalMeshComponent* TriggerMesh;

    /** Ʈ���� �̸� */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger Info")
    FString PartName;

    /** Ʈ���� ������ */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger Info")
    float Damage;

    /** źâ ũ�� */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger Info")
    int32 MagazineCapacity;

    /** ������ �ؽ�ó */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
    UTexture2D* IconTexture;

    /** ������ �ؽ�ó ��� */
    FString IconTexturePath;

    /** Ʈ���� ���� �ʱ�ȭ �Լ� */
    virtual void Initialize(const FString& MeshName) override;

    /** Ʈ���� �޽��� ��ȯ�ϴ� �Լ� */
    virtual USkeletalMeshComponent* GetMesh() const override;

protected:
    UPROPERTY(VisibleAnywhere)
    USceneComponent* RootSceneComponent;

private:
    /** ������ �ε� �Լ� */
    void LoadIconTexture();
};
