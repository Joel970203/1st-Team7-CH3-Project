#include "Core/CP_GameState.h"
#include "Core/CP_AISpawnPoint.h"
#include "Core/CP_PlayerHUD.h"
#include "Core/CP_GameInstance.h"

#include "Character/CP_PlayerController.h"
#include "Character/CP_NormalEnemy.h"
#include "Character/CP_CoverEnemy.h"

#include "Kismet/GameplayStatics.h"
#include "Cyberpunk.h"


ACP_GameState::ACP_GameState()
{
	Wave = 1;
	MAX_Wave = 4;
	Dealay_Time = 2.0f;
	Number_AI = 0;
	AI_Counting = 0;
}

void ACP_GameState::BeginPlay()
{
	Super::BeginPlay();

	StartWave();

}

void ACP_GameState::StartWave()
{
	UCP_GameInstance* GameInstance = Cast<UCP_GameInstance>(UGameplayStatics::GetGameInstance(this));

	UE_LOG(LogTemp, Warning, TEXT("StartWave : %d"), Wave);
	GameInstance->AddPlayerHUDToViewport();
	GameInstance->Set_Wave(Wave);
	AI_Spawn_Owner(); //ai spawn �Լ�

}


void ACP_GameState::OnGameOver()//���� ���� �Լ�
{
	CP_LOG(Warning, TEXT("GameOver"));

	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (ACP_PlayerController* CP_PlayerController = Cast<ACP_PlayerController>(PlayerController))
		{
			CP_PlayerController->SetPause(true);
			// CP_PlayerHUD->ShowMainMenu(); //�̱���
		}
	}
}

void ACP_GameState::KillAll()//AI�� ��� �׾��� �� ȣ��
{
	UE_LOG(LogTemp, Warning, TEXT("Kill All"));
	UCP_GameInstance* Instance = Cast<UCP_GameInstance>(UGameplayStatics::GetGameInstance(this));

	if (Wave < MAX_Wave)
	{
		Wave++;
		StartWave();
	}
	else //������ ����
	{
		OnGameOver();

	}
	Instance->Set_Wave(Wave);

}

//AI ���� �Լ�
void ACP_GameState::AI_Spawn_Owner()
{
	TArray<AActor*> FoundActors;
	TArray<ACP_AISpawnPoint*> Portal;

	if (Wave < MAX_Wave) Number_AI = ((Wave * 3) + 1) / 2; // 2, 3, 5, 6
	else Number_AI = 1;

	UCP_GameInstance* GameInstance = Cast<UCP_GameInstance>(UGameplayStatics::GetGameInstance(this));
	GameInstance->Set_AICount(Number_AI);
	if (!EnemyClass)  // �������Ʈ���� ������ �� �Ǿ��� ��� ��� �ڵ�
	{
		CP_LOG(Warning, TEXT("EnemyClass Didn't Enable"));
		return;
	}

	//����󿡼� ACP_AISpawnPoint ��ü�� ��� ã�� FoundActors�� Push
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACP_AISpawnPoint::StaticClass(), FoundActors);
	int Portal_Number = FoundActors.Num(); //������ �� ���� ����

	if (Portal_Number > 0)
	{
		Portal.SetNum(Portal_Number);
		for (int32 i = 0; i < Portal_Number; i++)
		{
			Portal[i] = Cast<ACP_AISpawnPoint>(FoundActors[i]);
			SpawnLocation.Push(Portal[i]->PortalLocation());
		}

		SpawnParams.Owner = this;

		//������ġ �浹�� ���� ��� ��ġ ������ ����
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		if (Wave < MAX_Wave)
		{
			GetWorldTimerManager().SetTimer(
				AIWatingTimerHandel,
				std::bind(&ACP_GameState::Spawner, this, Portal_Number),
				Dealay_Time,
				true
			);
		}
		else
		{
			Boss_Spawner(Portal_Number);
		}
	}
}

void ACP_GameState::Spawner(int32 Portal_Number)
{
	for (int i = 0; i < Portal_Number; i++)
	{
		AActor* SpawnedAI;
		if (i % 3 == 0)
		{
			SpawnedAI = GetWorld()->SpawnActor<AActor>(
				EnemyClass,
				SpawnLocation[i],
				FRotator::ZeroRotator,
				SpawnParams
			);
		}
		else
		{
			SpawnedAI = GetWorld()->SpawnActor<AActor>(
				HiddenEnemyClass,
				SpawnLocation[i],
				FRotator::ZeroRotator,
				SpawnParams
			);
		}
		++AI_Counting;
		if (!SpawnedAI)
		{
			CP_LOG(Warning, TEXT("AI Spawn Failed"));
		}
		else
		{
			CP_LOG(Warning, TEXT("AI Spawn Success: %s"), *SpawnLocation[i].ToString());
		}
		if (AI_Counting == Number_AI)//AI�� �� �����Ǹ� ���� ����
		{
			GetWorldTimerManager().ClearTimer(AIWatingTimerHandel);
			AI_Counting = 0;
			break;
		}

	}
}

void ACP_GameState::Boss_Spawner(int32 Portal_Number)
{
	UClass* BossClass = LoadObject<UClass>(nullptr, TEXT("/Game/_Game/Enemy/BP_BossEnemy.BP_BossEnemy_C"));

	if (BossClass)
	{
		AActor* SpawnedAI = GetWorld()->SpawnActor<AActor>(BossClass, SpawnLocation[0], FRotator::ZeroRotator,
			SpawnParams);
		CP_LOG(Warning, TEXT("Boss Wave"));
	}
	++AI_Counting;
}

