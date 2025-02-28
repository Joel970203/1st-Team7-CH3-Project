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
	UPROPERTY(EditDefaultsOnly, Category = "Setting")
	TSubclassOf<AActor> HiddenEnemyClass; //������ų ai Ÿ��
	UPROPERTY(EditDefaultsOnly, Category = "Setting")
	int32 Portal_Nums; //������ų ��Ż ����

	int32 Wave; //���̺� �ܰ�
	int32 Number_AI; //������ AI ��
	int32 AI_Counting; //������ AI ��
	FTimerHandle AIWatingTimerHandel; //ai���� ���� ���ð� Ÿ�̸�
	FTimerHandle PlayTimerHandle; // �� �÷��� Ÿ�� Ÿ�̸�
	FActorSpawnParameters SpawnParams;

	void StartWave(); //Wave ���� �Լ�
	void SpawnPortal(); //������ġ ���� �����Լ�
	void OnGameOver(); //ĳ���� ü���� 0�� ���� ��, �������� ������ ��
	void KillAll(); //��� ���� ����� �� ȣ��
	void AI_Spawn_Owner(); //���̺갡 ���� ������ �� ���� �����ϴ� �Լ�
	void Spawner(TArray<FVector> SpawnLocation);
	void Boss_Spawner(TArray<FVector> SpawnLocation); //������ ���� �Լ�
};
