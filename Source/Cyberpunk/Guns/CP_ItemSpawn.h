#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "CP_Ammo.h"
#include "CP_Gear.h"
#include "CP_Heal.h"
#include "Character/CP_Player.h"
#include "Inventory/CP_ItemInfo.h"
#include "CP_ItemSpawn.generated.h"

UCLASS()
class CYBERPUNK_API ACP_ItemSpawn : public AActor
{
    GENERATED_BODY()

public:
    ACP_ItemSpawn();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

private:
    /** ������ ���� �Լ� */
    void SpawnItem();

    /** ������ ȹ�� �� ȣ�� */
    UFUNCTION()
    void OnItemOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
        const FHitResult& SweepResult);

    /** �������� ������ ������ ���� */
    FCP_ItemInfo SpawnedItemInfo;

    /** ������ ������ ���� */
    AActor* SpawnedItem;

    /** ��Ʈ ������Ʈ */
    UPROPERTY()
    USceneComponent* RootScene;

    /** �浹 ������Ʈ */
    UPROPERTY()
    USphereComponent* CollisionComponent;

    /** Ammo, Gear, Heal Ŭ���� ���� */
    UPROPERTY()
    TSubclassOf<AActor> AmmoClass;

    UPROPERTY()
    TSubclassOf<AActor> GearClass;

    UPROPERTY()
    TSubclassOf<AActor> HealClass;

    /** �ʱ� ���� ��ġ */
    FVector InitialSpawnLocation;

    /** �ð� ��� */
    float TimeElapsed;
};
