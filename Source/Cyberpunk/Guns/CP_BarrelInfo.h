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

    // �跲 �޽�
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Barrel Info")
    USkeletalMeshComponent* BarrelMesh;

    // �跲 �̸�
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Barrel Info")
    FString PartName;

    // �跲 ������ �ؽ�ó (��� ������� �ε�)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    FString IconTexturePath;

    // ������ �ؽ�ó (�ε�� �ؽ�ó)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
    UTexture2D* IconTexture;

    // ��Ʈ��ĵ ����
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Barrel Info")
    bool bIsHitscan;

    // �跲 ������
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Barrel Info")
    float Damage;

    int32 GearCost;

    int32 GetGearCost() const { return GearCost; }

    // �ʱ�ȭ �Լ�
    virtual void Initialize(const FString& MeshName) override;

    // ������ �ε� �Լ�
    void LoadIconTexture();

    virtual USkeletalMeshComponent* GetMesh() const override;

    UFUNCTION(BlueprintCallable, Category = "Gun Info")
    FString GetPartName() const { return PartName; }

    UFUNCTION(BlueprintCallable, Category = "Gun Info")
    float GetDamage() const { return Damage; }

    UFUNCTION(BlueprintCallable, Category = "Gun Info")
    bool IsHitscan() const { return bIsHitscan; }

protected:
    UPROPERTY(VisibleAnywhere)
    USceneComponent* RootSceneComponent;
};
