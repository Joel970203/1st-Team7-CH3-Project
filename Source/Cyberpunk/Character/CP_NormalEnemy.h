#pragma once

#include "CoreMinimal.h"
#include "Character/CP_Enemy.h"
#include "Guns/CP_Guns.h"
#include "CP_NormalEnemy.generated.h"

/**
 * 
 */
UCLASS()
class CYBERPUNK_API ACP_NormalEnemy : public ACP_Enemy
{
	GENERATED_BODY()
	
public:
	
	ACP_NormalEnemy();

protected:

	virtual void BeginPlay() override;

public:

	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void AttackNormal() override;

protected:

	virtual void Die() override;
	UPROPERTY()
	ACP_Guns* Gun;  // ���� �ν��Ͻ�

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<ACP_Guns> GunClass;  // ���� Ŭ���� ����
};
