#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "CP_GameState.generated.h"


UCLASS()
class CYBERPUNK_API ACP_GameState : public AGameState
{
	GENERATED_BODY()
public:

	ACP_GameState();
	virtual void BeginPlay() override;



	int32 Wave;
	int32 AI_Count;
	float WatingTime;


	FTimerHandle AIWatingTimerHandel; //ai���� ���� ���ð� Ÿ�̸�
	FTimerHandle PlayTimerHandle; // �� �÷��� Ÿ�� Ÿ�̸�

	void StartWave(); //Wave ���� �Լ�
	void StartBossWave(); //������ ���� �Լ�
	void OnGameOver(); //ĳ���� ü���� 0�� ���� ��� ȣ��
	void KillAll(); //��� ���� ����� �� ȣ��
	void SpawnAI(); //���̺갡 ���� ������ �� ���� �����ϴ� �Լ�
	FVector GetRandomSpawnLocation();
};
