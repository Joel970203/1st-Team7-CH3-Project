#include "Core/CP_GameMode.h"
#include "Character/CP_Player.h"
#include "Character/CP_PlayerController.h"
#include "Core/CP_GameState.h"
#include "Character/CP_Enemy.h"
#include "Guns/CP_ItemSpawn.h"
#include "EngineUtils.h"  

ACP_GameMode::ACP_GameMode()
{
    DefaultPawnClass = ACP_Player::StaticClass();
    PlayerControllerClass = ACP_PlayerController::StaticClass();
    GameStateClass = ACP_GameState::StaticClass();
}

void ACP_GameMode::BeginPlay()
{
    Super::BeginPlay();

    // World ��ȿ�� üũ
    UWorld* World = GetWorld();
    if (!World)
    {
        UE_LOG(LogTemp, Error, TEXT("[ACP_GameMode] ERROR: GetWorld() returned nullptr!"));
        return;
    }

    // ��� ���� ã��, �̺�Ʈ ���ε�
    for (TActorIterator<ACP_Enemy> It(World); It; ++It)
    {
        ACP_Enemy* Enemy = *It;
        if (Enemy)
        {
            Enemy->OnEnemyDeadDelegate.AddDynamic(this, &ACP_GameMode::SpawnItemOnEnemyDeath);
            UE_LOG(LogTemp, Log, TEXT("[ACP_GameMode] Bound OnEnemyDeadDelegate event for %s"), *Enemy->GetName());
        }
    }
}

//  ���Ͱ� ������ ������ ���
void ACP_GameMode::SpawnItemOnEnemyDeath(const FVector& DeathLocation)
{
    float DropChance = 0.5f; // 50% Ȯ��

    if (FMath::RandRange(0.0f, 1.0f) <= DropChance)
    {
        UE_LOG(LogTemp, Log, TEXT("[ACP_GameMode] Spawning ACP_ItemSpawn at %s"), *DeathLocation.ToString());

        // `ACP_ItemSpawn` ����
        GetWorld()->SpawnActor<ACP_ItemSpawn>(ACP_ItemSpawn::StaticClass(), DeathLocation, FRotator::ZeroRotator);
    }
}
