#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CP_GunPart.h"
#include "Engine/Texture2D.h"
#include "CP_BodyInfo.generated.h"

UCLASS(Blueprintable)
class CYBERPUNK_API ACP_BodyInfo : public AActor, public IGunPart
{
    GENERATED_BODY()

public:
    ACP_BodyInfo();

    /** BodyMesh �ʱ�ȭ */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Info")
    USkeletalMeshComponent* BodyMesh;

    /** �ٵ� �̸� */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Info")
    FString PartName;

    /** �ٵ� ������ */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Info")
    float Damage;

    /** �̵� �ӵ� */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Info")
    float MovementSpeed;

    /** ������ �ؽ�ó */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
    UTexture2D* IconTexture;

    /** ������ �ؽ�ó ��� */
    FString IconTexturePath;

    /** Body ���� �ʱ�ȭ �Լ� */
    virtual void Initialize(const FString& MeshName) override;

    /** BodyMesh ��ȯ �Լ� */
    virtual USkeletalMeshComponent* GetMesh() const override;

protected:
    UPROPERTY(VisibleAnywhere)
    USceneComponent* RootSceneComponent;

private:
    /** ������ �ε� �Լ� */
    void LoadIconTexture();
};
