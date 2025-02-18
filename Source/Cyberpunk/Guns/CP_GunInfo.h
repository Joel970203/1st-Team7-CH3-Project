#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CP_GunInfo.generated.h"

UCLASS()
class CYBERPUNK_API ACP_GunInfo : public AActor
{
    GENERATED_BODY()

public:
    ACP_GunInfo();

    // �ѱ� �̸� (���� ������ �̸��� ���⿡�� ����)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Info")
    FString GunName;

 
    // GunInfo ���� �Ӽ����� �����ϴ� Ŭ����
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Parts")
    ACP_GunInfo* BarrelInfo; // Barrel ���� ����

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Parts")
    ACP_GunInfo* BodyInfo; // Body ���� ����

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Parts")
    ACP_GunInfo* TriggerInfo; // Trigger ���� ����


    /*
    // ������ ���� (Scope_Info�� �ڽ� Ŭ�������� ��ӹ޾� ���� ������ ����)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Parts")
    UGun_Info* ScopeInfo;
    */
};
