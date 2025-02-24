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


	UPROPERTY(EditDefaultsOnly, Category = "Setting")
	int32 MAX_Wave; //Wave ��
	UPROPERTY(EditDefaultsOnly, Category = "Setting")
	float Dealay_Time; //�������� ������ Ÿ��
	UPROPERTY(EditDefaultsOnly, Category = "Setting")
	TSubclassOf<AActor> EnemyClass; //������ų ai Ÿ��


	int32 Wave;
	int32 Number_AI; //�Ű�Ⱦ��ŵ� �˴ϴ�
	int32 AI_Counting; //������ų AI��
	FTimerHandle AIWatingTimerHandel; //ai���� ���� ���ð� Ÿ�̸�
	FTimerHandle PlayTimerHandle; // �� �÷��� Ÿ�� Ÿ�̸�
	FVector SpawnLocation;
	FActorSpawnParameters SpawnParams;

	void StartWave(); //Wave ���� �Լ�
	void StartBossWave(); //������ ���� �Լ�
	void OnGameOver(); //ĳ���� ü���� 0�� ���� ��� ȣ��
	void KillAll(); //��� ���� ����� �� ȣ��
	void AI_Spawn_Owner(); //���̺갡 ���� ������ �� ���� �����ϴ� �Լ�
	void Spawner();
};
