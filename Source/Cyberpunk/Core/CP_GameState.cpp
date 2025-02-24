
#include "Core/CP_GameState.h"
#include "Character/CP_PlayerController.h"
#include "Core/CP_PlayerHUD.h"
#include "Character/CP_NormalEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "Core/CP_AISpawnPoint.h"
#include "Cyberpunk.h"


ACP_GameState::ACP_GameState()
{
	Wave = 1;
	MAX_Wave = 3;
	Dealay_Time = 2.0f;
	Number_AI = 0;
	AI_Counting = 0;
	SpawnLocation = { 0,0,0 };
}

void ACP_GameState::BeginPlay()
{
	Super::BeginPlay();

	StartWave();

}

void ACP_GameState::StartWave()
{
	UE_LOG(LogTemp, Warning, TEXT("StartWave : %d"), Wave);

	AI_Spawn_Owner(); //ai spawn �Լ�

}

void ACP_GameState::StartBossWave()
{
	UE_LOG(LogTemp, Warning, TEXT("Boss Wave"));

}

void ACP_GameState::OnGameOver()//���� ���� �Լ�
{
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

	if (Number_AI >= 0 && Wave <= 2)// ai�� ��� �װ� ���� ���̺갡 2���ϸ� ���� ���̺� ����
	{
		Wave++;
		StartWave();
	}
	else if (Number_AI >= 0 && Wave > 2) // 3���̺긦 ���´ٸ� ������ ����
	{
		Wave++;
		StartBossWave();
	}
	else //������ ����
	{
		if (Wave > 3)
		{
			OnGameOver();
		}
	}
}

void ACP_GameState::Spawner()
{
	AActor* SpawnedAI = GetWorld()->SpawnActor<AActor>(
		EnemyClass,
		SpawnLocation,
		FRotator::ZeroRotator,
		SpawnParams
	);

	AI_Counting++;
	if (!SpawnedAI)  // AI ������ ������ ���
	{
		CP_LOG(Warning, TEXT("AI Spawn Failed"));
	}
	else  // AI ������ ������ ���
	{
		CP_LOG(Warning, TEXT("AI Spawn Success: %s"), *SpawnLocation.ToString());
	}

	if (AI_Counting >= Number_AI)//AI�� �� �����Ǹ� ���� ����
	{
		GetWorldTimerManager().ClearTimer(AIWatingTimerHandel);
		AI_Counting = 0;
		KillAll();
	}
}

//AI ���� �Լ�
void ACP_GameState::AI_Spawn_Owner()
{

	Number_AI = ((Wave * 3) + 1) / 2; // 2, 3, 5, 6

	if (!EnemyClass)  // �������Ʈ���� ������ �� �Ǿ��� ��� ��� �ڵ�
	{
		CP_LOG(Warning, TEXT("EnemyClass Didn't Enable"));
		return;
	}

	TArray<AActor*> FoundActors;

	//����󿡼� ACP_AISpawnPoint ��ü�� ��� ã�� FoundActors�� Push
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACP_AISpawnPoint::StaticClass(), FoundActors);

	//��ü�� �����Ѵٸ� ����
	if (FoundActors.Num() > 0)
	{
		//AActor*�� ACP_AISpawnPoint* �� ĳ����
		ACP_AISpawnPoint* SpawnPortal = Cast<ACP_AISpawnPoint>(FoundActors[0]);
		if (SpawnPortal)
		{
			SpawnLocation = SpawnPortal->PortalLocation();
			SpawnParams.Owner = this;

			//������ġ �浹�� ���� ��� ��ġ ������ ����
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			GetWorldTimerManager().SetTimer(
				AIWatingTimerHandel,
				this,
				&ACP_GameState::Spawner,
				Dealay_Time,
				true
			);
		}
	}
}