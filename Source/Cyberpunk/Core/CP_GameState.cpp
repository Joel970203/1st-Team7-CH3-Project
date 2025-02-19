
#include "Core/CP_GameState.h"
#include "Character/CP_PlayerController.h"

ACP_GameState::ACP_GameState()
{
	Wave = 0;
	WatingTime = 3.0f;
	AI_Count = 0;
}

void ACP_GameState::BeginPlay()
{
	Super::BeginPlay();

	StartWave();

}

void ACP_GameState::StartWave()
{
	SpawnAI();
	//AI�������� WatingTime�ʰ� ������ �̵����� �̵��Լ� �̱������� �ּ�ó��.
	/*GetWorldTimerManager().SetTimer(
		AIWatingTimerHandel,
		this,
		&CP_EnemyAI::StartMove,
		WatingTime,
		false
	);*/




}

void ACP_GameState::StartBossWave()
{
}

void ACP_GameState::OnGameOver()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (ACP_PlayerController* CP_PlayerController = Cast<ACP_PlayerController>(PlayerController))
		{
			CP_PlayerController->SetPause(true);
			// CP_PlayerController->ShowMainMenu(true); //�̱���
		}
	}
}

void ACP_GameState::KillAll()
{
	if (AI_Count >= 0 && Wave <= 3)// ai�� ��� �װ� ���� ���̺갡 2���ϸ� ���� ���̺� ����
	{
		StartWave();
	}
	else if (AI_Count >= 0 && Wave > 2) // 3���̺긦 ���´ٸ� ������ ����
	{
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

void ACP_GameState::SpawnAI()
{
}
